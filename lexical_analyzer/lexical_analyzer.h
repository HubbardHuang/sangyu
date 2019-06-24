#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>
#include <memory>
#include <vector>

#include "dfa.h"

namespace sangyu {

struct Token {
    using Type = std::string;

    static const Type kNum;
    static const Type kId;
    static const Type kLtrChar;
    static const Type kLtrStr;
    static const Type kComment;

    std::string name;
    Type type;
    Token(const std::string& n, const Type& t);
    Token(const Token&);
    Token() = delete;
};

enum DfaType {
    kSpaceDfa = 0, // If the first one isn't 0, 'std::bad_alloc' will be thrown
    kPunctuationDfa,
    kKeywordDfa,
    kNumDfa,
    kIdDfa,
    kCharacterLiteralDfa,
    kStringLiteralDfa,
    kCommentDfa
};

class LexicalAnalyzer {
private:
    std::vector<std::shared_ptr<DFA>> analyzer_;

public:
    LexicalAnalyzer(
      const std::vector<std::pair<std::shared_ptr<DFA>, DfaType>>& analyzer);
    ~LexicalAnalyzer() = default;

public:
    std::vector<Token> Run(std::fstream& file, std::ostream& os = std::cout);

private:
    LexicalAnalyzer() = delete;
    LexicalAnalyzer(const LexicalAnalyzer&) = delete;
    LexicalAnalyzer(LexicalAnalyzer&&) = delete;
    void operator=(const LexicalAnalyzer&) = delete;
    void operator=(LexicalAnalyzer&&) = delete;
};

} // namespace sangyu

#endif