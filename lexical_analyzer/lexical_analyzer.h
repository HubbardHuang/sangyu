#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>
#include <memory>
#include <vector>

#include "dfa.h"

namespace sangyu {

enum TokenType {
    kNum = 128,
    kId,

    kInt,
    kChar,
    kConst,
    kReturn,
    kInclude,

    kCharacterLiteral,
    kStringLiteral,
    kComment
};

struct Token {
    std::string name;
    int type;
    Token(const std::string& n, int t);
    Token(const Token&);
    Token() = delete;
};

enum class DfaType {
    kSpace,
    kPunctuation,
    kKeyword,
    kNum,
    kId,
    kComment,
    kCharacterLiteral,
    kStringLiteral
};

struct DfaAndType {
    std::shared_ptr<DFA> dfa;
    DfaType type;
    DfaAndType(std::shared_ptr<DFA> d, DfaType t);
    DfaAndType(const DfaAndType&);
    DfaAndType() = delete;
};

class LexicalAnalyzer {
private:
    std::vector<DfaAndType> analyzer_;

public:
    LexicalAnalyzer(const std::vector<DfaAndType>& analyzer);
    ~LexicalAnalyzer() = default;

public:
    std::vector<Token> Run(std::fstream& file);

private:
    LexicalAnalyzer() = delete;
    LexicalAnalyzer(const LexicalAnalyzer&) = delete;
    LexicalAnalyzer(LexicalAnalyzer&&) = delete;
    void operator=(const LexicalAnalyzer&) = delete;
    void operator=(LexicalAnalyzer&&) = delete;
};

} // namespace sangyu

#endif