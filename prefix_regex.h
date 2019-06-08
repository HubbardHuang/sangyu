#ifndef PREFIX_REGEX_H
#define PREFIX_REGEX_H

#include <list>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class PrefixRegex : public RegexDefinition {
private:
    std::list<unit_type> buffer_;
    std::string prefix_regex_;

private:
    static std::string ToPrefixExpression(std::list<unit_type>& buffer);
    static void ReplaceOperators(std::list<unit_type>& buffer);
    static void AddJoinOperator(std::list<unit_type>& buffer);
    static void AddStartSymbolAndStopSymbol(std::list<unit_type>& buffer);

public:
    ~PrefixRegex() = default;
    PrefixRegex(const std::string& source);
    const std::string& GetValue(void) const;

private:
    PrefixRegex() = delete;
    PrefixRegex(const PrefixRegex&) = delete;
    PrefixRegex(PrefixRegex&&) = delete;
    void operator=(const PrefixRegex&) = delete;
    void operator=(PrefixRegex&&) = delete;
};

} // namespace sangyu

#endif