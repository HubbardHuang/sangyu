#ifndef PREPROCESSED_REGEX_H
#define PREPROCESSED_REGEX_H

#include <list>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class PreprocessedRegex : public RegexDefinition {
private:
    std::list<unit_type> buffer_;
    std::string prefix_regex_;

private:
    static std::string ToPrefixExpression(std::list<unit_type>& buffer);
    static void ReplaceOperators(std::list<unit_type>& buffer);
    static void AddJoinOperator(std::list<unit_type>& buffer);
    static void AddStartSymbolAndStopSymbol(std::list<unit_type>& buffer);

public:
    ~PreprocessedRegex() = default;
    PreprocessedRegex(const std::string& source);
    const std::string& GetValue(void) const;

private:
    PreprocessedRegex() = delete;
    PreprocessedRegex(const PreprocessedRegex&) = delete;
    PreprocessedRegex(PreprocessedRegex&&) = delete;
    void operator=(const PreprocessedRegex&) = delete;
    void operator=(PreprocessedRegex&&) = delete;
};

} // namespace sangyu

#endif