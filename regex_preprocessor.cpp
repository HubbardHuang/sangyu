#include <cctype>
#include <vector>

#include "regex_preprocessor.h"

namespace sangyu {

RegexPreprocessor::RegexPreprocessor(const std::string& source)
  : buffer_(source.begin(), source.end()) {}

std::string
RegexPreprocessor::Run(void) {
    ReplaceOperators();
    AddJoinOperator();
    // AddStartSymbolAndStopSymbol();
    return std::string(buffer_.begin(), buffer_.end());
}

void
RegexPreprocessor::ReplaceOperators(void) {
    if (buffer_.empty()) {
        return;
    }
    for (auto curr = buffer_.begin(); curr != buffer_.end(); ++curr) {
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
            curr = buffer_.erase(curr);
            break;
        default:
            break;
        }
    }
}

void
RegexPreprocessor::AddJoinOperator(void) {
    if (buffer_.empty()) {
        return;
    }
    auto curr = buffer_.begin();
    auto next = buffer_.begin();
    next++;
    for (; next != buffer_.end(); curr++, next++) {
        if (isprint(*curr) && isprint(*next) /* ab */ ||
            *curr == kClosureOperator_ && isprint(*next) /* a*b */ ||
            *curr == kRightBracket_ && isprint(*next) /* (a)b */ ||
            isprint(*curr) && *next == kLeftBracket_ /*a(b)*/ ||
            *curr == kRightBracket_ && *next == kLeftBracket_ /* (a)(b) */) {
            next = buffer_.insert(next, kJoinOperator_);
        }
    }
}

void
RegexPreprocessor::AddStartSymbolAndStopSymbol(void) {
    buffer_.push_front(kStartSymbol_);
    buffer_.push_back(kStopSymbol_);
}

} // namespace sangyu