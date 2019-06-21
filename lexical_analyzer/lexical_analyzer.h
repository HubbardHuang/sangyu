#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>

#include "dfa.h"

namespace sangyu {

class LexicalAnayzer {
private:
    DFA dfa_;

public:
    LexicalAnayzer(std::fstream& source);
    ~LexicalAnayzer() = default;

private:
    LexicalAnayzer() = delete;
    LexicalAnayzer(const LexicalAnayzer&) = delete;
    LexicalAnayzer(LexicalAnayzer&&) = delete;
    void operator=(const LexicalAnayzer&) = delete;
    void operator=(LexicalAnayzer&&) = delete;
};

} // namespace sangyu

#endif