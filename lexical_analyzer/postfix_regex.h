#ifndef POSTFIX_REGEX_H
#define POSTFIX_REGEX_H

#include <iostream>
#include <map>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class PreprocessedRegex;

class PostfixRegex : public RegexDefinition {
private:
    std::string postfix_regex_;

private:
    static std::string ToPostfixExpression(const std::string& source);

public:
    ~PostfixRegex() = default;
    explicit PostfixRegex(const PreprocessedRegex& source);
    const std::string& GetValue(void) const;
    void Test(std::ostream& os = std::cout);

private:
    PostfixRegex() = delete;
    PostfixRegex(const PostfixRegex&) = delete;
    PostfixRegex(PostfixRegex&&) = delete;
    void operator=(const PostfixRegex&) = delete;
    void operator=(PostfixRegex&&) = delete;
};

} // namespace sangyu

#endif