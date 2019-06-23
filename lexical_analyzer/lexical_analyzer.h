#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <fstream>
#include <memory>
#include <vector>

#include "dfa.h"

namespace sangyu {

class LexicalAnalyzer {
public:
    LexicalAnalyzer(std::vector<std::unique_ptr<DFA>>);
};

} // namespace sangyu

#endif