#include <cassert>
#include <stack>
#include <vector>

#include "postfix_regex.h"
#include "prefix_regex.h"

namespace sangyu {

PostfixRegex::PostfixRegex(const PrefixRegex& source)
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
                while (!operator_stack.empty() &&
                       priority[operator_stack.top()] >= priority[c]) {
                    auto temp = operator_stack.top();
                    if (IsValueUnit(temp)) {
                        result.push_back(temp);
                    }
                    operator_stack.pop();
                }
                operator_stack.push(c);
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

} // namespace sangyu