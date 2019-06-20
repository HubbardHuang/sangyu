#include <cassert>
#include <stack>
#include <vector>

#include "postfix_regex.h"
#include "preprocessed_regex.h"

namespace sangyu {

PostfixRegex::PostfixRegex(const PreprocessedRegex& source)
  : postfix_regex_(ToPostfixExpression(source.GetValue())) {}

const std::string&
PostfixRegex::GetValue(void) const {
    return postfix_regex_;
}

std::string
PostfixRegex::ToPostfixExpression(const std::string& source) {
    std::stack<PostfixRegex::unit_type> operator_stack;
    std::vector<PostfixRegex::unit_type> result;
    for (auto c : source) {
        if (IsOperator(c)) {
            if (operator_stack.empty()) {
                operator_stack.push(c);
            } else {
                /* new */
                if (c == kLeftRoundBracket_) {
                    operator_stack.push(c);
                } else if (c == kRightRoundBracket_) {
                    while (!operator_stack.empty() &&
                           operator_stack.top() != kLeftRoundBracket_) {
                        result.push_back(operator_stack.top());
                        operator_stack.pop();
                    }
                    if (!operator_stack.empty()) {
                        operator_stack.pop();
                    }
                } else {
                    while (!operator_stack.empty() &&
                           priority[operator_stack.top()] >= priority[c]) {
                        auto temp = operator_stack.top();
                        if (IsValueUnit(temp)) {
                            if (c == kClosureOperator_ &&
                                temp == kClosureOperator_) {
                                // Do nothing
                            } else {
                                result.push_back(temp);
                            }
                        }
                        operator_stack.pop();
                    }
                    operator_stack.push(c);
                }
                /* old */
                // while (!operator_stack.empty() &&
                //        priority[operator_stack.top()] >= priority[c]) {
                //     auto temp = operator_stack.top();
                //     if (IsValueUnit(temp)) {
                //         result.push_back(temp);
                //     }
                //     operator_stack.pop();
                // }
                // operator_stack.push(c);
            }
        } else {
            result.push_back(c);
        }
    }
    while (!operator_stack.empty()) {
        auto temp = operator_stack.top();
        if (IsValueUnit(temp)) {
            result.push_back(temp);
        }
        operator_stack.pop();
    }
    return std::string(result.begin(), result.end());
}

std::string
PostfixRegex::Test(void) {
    std::string result;
    for (auto ch = postfix_regex_.begin(); ch != postfix_regex_.end(); ch++) {
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