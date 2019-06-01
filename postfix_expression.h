#ifndef POSTFIX_EXPRESSION_H
#define POSTFIX_EXPRESSION_H

#include <map>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class PostfixExpressionConverter : public RegexDefinition {
private:
    std::string regex;

private:
    static std::map<unit_type, size_t> priority;

private:
    bool IsOperator(unit_type u);
    bool IsValueUnit(unit_type u);
    void ToPostfixExpression(void);

public:
    ~PostfixExpressionConverter() = default;
    PostfixExpressionConverter(const std::string& source);
    std::string GetResult(void);

private:
    PostfixExpressionConverter() = delete;
    PostfixExpressionConverter(const PostfixExpressionConverter&) = delete;
    PostfixExpressionConverter(PostfixExpressionConverter&&) = delete;
    void operator=(const PostfixExpressionConverter&) = delete;
    void operator=(PostfixExpressionConverter&&) = delete;
};

} // namespace sangyu

#endif