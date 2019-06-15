#include <cctype>
#include <vector>

#include "preprocessed_regex.h"

namespace sangyu {

PreprocessedRegex::PreprocessedRegex(const std::string& source)
  : buffer_(source.begin(), source.end())
  , prefix_regex_(ToPrefixExpression(buffer_)) {}

std::string
PreprocessedRegex::ToPrefixExpression(std::list<unit_type>& buffer) {
    ReplaceOperators(buffer);
    AddJoinOperator(buffer);
    // AddStartSymbolAndStopSymbol(buffer);
    return std::string(buffer.begin(), buffer.end());
}

const std::string&
PreprocessedRegex::GetValue(void) const {
    return prefix_regex_;
}

void
PreprocessedRegex::ReplaceOperators(std::list<unit_type>& buffer) {
    if (buffer.empty()) {
        return;
    }
    for (auto curr = buffer.begin(); curr != buffer.end(); ++curr) {
        switch (*curr) {
        case '(':
            *curr = kLeftBracket_;
            break;
        case ')':
            *curr = kRightBracket_;
            break;
        case '*':
            *curr = kClosureOperator_;
            break;
        case '|':
            *curr = kOrOperator_;
            break;
        case '\\':
            curr = buffer.erase(curr);
            break;
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
        if (isprint(*curr) && isprint(*next) /* ab */ ||
            *curr == kClosureOperator_ && isprint(*next) /* a*b */ ||
            *curr == kRightBracket_ && isprint(*next) /* (a)b */ ||
            isprint(*curr) && *next == kLeftBracket_ /*a(b)*/ ||
            *curr == kRightBracket_ && *next == kLeftBracket_ /* (a)(b) */) {
            next = buffer.insert(next, kJoinOperator_);
        }
    }
}

void
PreprocessedRegex::AddStartSymbolAndStopSymbol(std::list<unit_type>& buffer) {
    buffer.push_front(kStartSymbol_);
    buffer.push_back(kStopSymbol_);
}

} // namespace sangyu