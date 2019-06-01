#ifndef REGEX_PREPROCESSOR_H
#define REGEX_PREPROCESSOR_H

#include <list>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class RegexPreprocessor : public RegexDefinition {
private:
    std::list<unit_type> buffer_;

private:
    void ReplaceOperators(void);
    void AddJoinOperator(void);
    void AddStartSymbolAndStopSymbol(void);

public:
    ~RegexPreprocessor() = default;
    RegexPreprocessor(const std::string& source);
    std::string Run(void);

private:
    RegexPreprocessor() = delete;
    RegexPreprocessor(const RegexPreprocessor&) = delete;
    RegexPreprocessor(RegexPreprocessor&&) = delete;
    void operator=(const RegexPreprocessor&) = delete;
    void operator=(RegexPreprocessor&&) = delete;
};

} // namespace sangyu

#endif