#include <cctype>
#include <iostream>
#include <stack>
#include <vector>

#include "preprocessed_regex.h"

namespace sangyu {

const std::set<PreprocessedRegex::unit_type>
  PreprocessedRegex::kAbbreviatedCharacters_ = { 'd', 'w', 'p', 's' };
const std::set<PreprocessedRegex::unit_type>
  PreprocessedRegex::kEscapeCharacters_ = { '\\', '\'', '\"', 'b', 'a',
                                            'n',  'r',  'f',  't', 'v' };
const std::set<PreprocessedRegex::unit_type>
  PreprocessedRegex::kSpecialCharacters_ = { '(', ')', '*', '|' };

PreprocessedRegex::PreprocessedRegex(const std::string& source)
  : buffer_(source.begin(), source.end())
  , preprocessed_regex_(ToPreprocessedExpression(buffer_)) {}

std::string
PreprocessedRegex::ToPreprocessedExpression(std::list<unit_type>& buffer) {
    if (!CheckSyntax(buffer)) {
        return "";
    }
    ProcessExtensionSyntax(buffer);
    // ReplaceOperators(buffer);
    AddJoinOperator(buffer);
    return std::string(buffer.begin(), buffer.end());
}

const std::string&
PreprocessedRegex::GetValue(void) const {
    return preprocessed_regex_;
}

bool
PreprocessedRegex::CheckSyntax(std::list<unit_type>& buffer) {
    auto left = buffer.begin();
    auto right = buffer.begin();
    right++;
    while (left != buffer.end() || right != buffer.end()) {
        if (left == buffer.end()) {
            break;
        }
        switch (*left) {
        case '\\':
            if (right == buffer.end()) {
                // Error
                std::cout << "Error: \'\\\' at the end." << std::endl;
                return false;
            }
            if (kSpecialCharacters_.find(*right) != kSpecialCharacters_.end()) {
                left = buffer.erase(left);
                right++;
            } else if (kEscapeCharacters_.find(*right) ==
                         kEscapeCharacters_.end() &&
                       kAbbreviatedCharacters_.find(*right) ==
                         kAbbreviatedCharacters_.end()) {
                // Error
                std::cout << "(1)Error: Illegal character \'" << *right
                          << "\' at the back of \'\\\'." << std::endl;
                return false;
            }
            break;
        case '(':
            *left = kLeftRoundBracket_;
            break;
        case ')':
            *left = kRightRoundBracket_;
            break;
        case '*':
            *left = kClosureOperator_;
            break;
        case '|':
            *left = kOrOperator_;
            break;
        default:
            break;
        }
        if (left != buffer.end()) {
            left++;
        }
        if (right != buffer.end()) {
            right++;
        }
    }

    std::stack<unit_type> symbol_stack;
    for (auto curr = buffer.begin(); curr != buffer.end(); curr++) {
        if (*curr == kLeftRoundBracket_) {
            symbol_stack.push(*curr);
            auto next = curr;
            next++;
            if (next != buffer.end() && *next == kRightRoundBracket_) {
                curr = buffer.erase(curr);
                curr = buffer.erase(curr);
                --curr;
            }
        } else if (*curr == kRightRoundBracket_) {
            if (!symbol_stack.empty()) {
                symbol_stack.pop();
            } else {
                // Error
                std::cout << "Error: Unbalanced symbols." << std::endl;
                return false;
            }
        }
    }

    return true;
}

void
PreprocessedRegex::ProcessExtensionSyntax(std::list<unit_type>& buffer) {
    auto left = buffer.begin();
    auto right = buffer.begin();
    right++;
    while (left != buffer.end() && right != buffer.end()) {
        if (*left == '\\') {
            switch (*right) {
            case 'd':
                buffer.insert(left, kDigits_.begin(), kDigits_.end());
                break;
            case 'w':
                buffer.insert(left, kLetters_.begin(), kLetters_.end());
                break;
            case 'p':
                buffer.insert(left, kCivilians_.begin(), kCivilians_.end());
                break;
            case 's':
                buffer.insert(left, kSpaces_.begin(), kSpaces_.end());
                break;
            default:
                // Error
                if (right == left)
                    std::cout << "(2)Error: Illegal character \'" << *right
                              << "\' at the back of \'" << *left << "\'. ["
                              << std::distance(buffer.begin(), right) << "]"
                              << std::endl;

                break;
            }
            left = buffer.erase(left);
            left = right = buffer.erase(left);
            if (right != buffer.end()) {
                ++right;
            }
        }
        if (right != buffer.end()) {
            ++left;
            ++right;
        }
    }
}

void
PreprocessedRegex::ReplaceOperators(std::list<unit_type>& buffer) {
    if (buffer.empty()) {
        return;
    }
    for (auto curr = buffer.begin(); curr != buffer.end(); ++curr) {
        switch (*curr) {
        case '(':
            *curr = kLeftRoundBracket_;
            break;
        case ')':
            *curr = kRightRoundBracket_;
            break;
        case '*':
            *curr = kClosureOperator_;
            break;
        case '|':
            *curr = kOrOperator_;
            break;
        // case '\\': // Remove?
        // curr = buffer.erase(curr);
        // break;
        default:
            break;
        }
    }
}

void
PreprocessedRegex::AddJoinOperator(std::list<unit_type>& buffer) {
    if (buffer.empty()) {
        return;
    }
    auto curr = buffer.begin();
    auto next = buffer.begin();
    next++;
    for (; next != buffer.end(); curr++, next++) {
        if (isascii(*curr) && isascii(*next) /* ab */ ||
            *curr == kClosureOperator_ && isascii(*next) /* a*b */ ||
            *curr == kClosureOperator_ &&
              *next == kLeftRoundBracket_ /* a*(b) */
            || *curr == kRightRoundBracket_ && isascii(*next) /* (a)b */ ||
            isascii(*curr) && *next == kLeftRoundBracket_ /* a(b) */ ||
            *curr == kRightRoundBracket_ &&
              *next == kLeftRoundBracket_ /* (a)(b) */) {
            next = buffer.insert(next, kJoinOperator_);
        }
    }
}

void
PreprocessedRegex::AddStartSymbolAndStopSymbol(std::list<unit_type>& buffer) {
    buffer.push_front(kStartSymbol_);
    buffer.push_back(kStopSymbol_);
}

std::string
PreprocessedRegex::Test(void) {
    std::string result;
    for (auto ch = preprocessed_regex_.begin(); ch != preprocessed_regex_.end();
         ch++) {
        std::string curr;
        if (*ch == kOrOperator_) {
            curr = "|";
        } else if (*ch == kClosureOperator_) {
            curr = "*";
        } else if (*ch == kLeftRoundBracket_) {
            curr = "(";
        } else if (*ch == kRightRoundBracket_) {
            curr = ")";
        } else if (*ch == kJoinOperator_) {
            curr = "&";
        } else if (*ch == '|' || *ch == '*' || *ch == '(' || *ch == ')') {
            curr =
              std::string("\\") + static_cast<std::string::value_type>(*ch);
        } else {
            curr = static_cast<std::string::value_type>(*ch);
        }
        if (!curr.empty()) {
            result += curr;
        }
    }
    return result;
}

} // namespace sangyu