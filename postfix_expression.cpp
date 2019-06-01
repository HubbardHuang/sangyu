#include <stack>
#include <vector>

#include "postfix_expression.h"

namespace sangyu {

std::map<PostfixExpressionConverter::unit_type, size_t>
  PostfixExpressionConverter::priority = {
      { PostfixExpressionConverter::kOrOperator_, 1 },
      { PostfixExpressionConverter::kJoinOperator_, 2 },
      { PostfixExpressionConverter::kClosureOperator_, 3 },
      { PostfixExpressionConverter::kRightBracket_, 0 },
      { PostfixExpressionConverter::kLeftBracket_, 0 }
  };

PostfixExpressionConverter::PostfixExpressionConverter(
  const std::string& source)
  : regex(source) {}

std::string
PostfixExpressionConverter::GetResult(void) {
    ToPostfixExpression();
    return regex;
}

bool
PostfixExpressionConverter::IsOperator(
  PostfixExpressionConverter::unit_type u) {
    return u < 0;
}

bool
PostfixExpressionConverter::IsValueUnit(
  PostfixExpressionConverter::unit_type u) {
    return u != kLeftBracket_ && u != kRightBracket_;
}

void
PostfixExpressionConverter::ToPostfixExpression(void) {
    std::stack<PostfixExpressionConverter::unit_type> operator_stack;
    std::vector<PostfixExpressionConverter::unit_type> result;
    for (auto c : regex) {
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
    regex = std::string(result.begin(), result.end());
}

} // namespace sangyu