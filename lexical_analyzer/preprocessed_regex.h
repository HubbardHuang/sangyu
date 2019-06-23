#ifndef PREPROCESSED_REGEX_H
#define PREPROCESSED_REGEX_H

#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>

#include "regex_definition.h"

namespace sangyu {

class PreprocessedRegex : public RegexDefinition {
private:
    std::fstream log_;
    std::list<unit_type> buffer_;
    std::string preprocessed_regex_;

private:
    static const std::set<unit_type> kAbbreviatedCharacters_;
    static const std::set<unit_type> kEscapeCharacters_;
    static const std::set<unit_type> kSpecialCharacters_;
    static const std::list<unit_type> kDigits_;
    static const std::list<unit_type> kLetters_;
    static const std::list<unit_type> kStringLiteralUnits_;
    static const std::list<unit_type> kSpaces_;
    static const std::list<unit_type> kPunctuation_;

private:
    static bool CheckSyntax(std::list<unit_type>& buffer);
    static void ProcessExtensionSyntax(std::list<unit_type>& buffer);
    static std::string ToPreprocessedExpression(std::list<unit_type>& buffer);
    static void ReplaceOperators(std::list<unit_type>& buffer);
    static void AddJoinOperator(std::list<unit_type>& buffer);
    static void AddStartSymbolAndStopSymbol(std::list<unit_type>& buffer);

public:
    ~PreprocessedRegex() = default;
    PreprocessedRegex(const std::string& source);
    const std::string& GetValue(void) const;
    void Test(std::ostream& os = std::cout);

private:
    PreprocessedRegex() = delete;
    PreprocessedRegex(const PreprocessedRegex&) = delete;
    PreprocessedRegex(PreprocessedRegex&&) = delete;
    void operator=(const PreprocessedRegex&) = delete;
    void operator=(PreprocessedRegex&&) = delete;
};

} // namespace sangyu

#endif