#include <iostream>

#include "lexical_analyzer.h"

namespace sangyu {

Token::Token(const std::string& n, int t)
  : name(n)
  , type(t) {}

Token::Token(const Token& source)
  : name(source.name)
  , type(source.type) {}

DfaAndType::DfaAndType(std::shared_ptr<DFA> d, DfaType t)
  : dfa(d)
  , type(t) {}

DfaAndType::DfaAndType(const DfaAndType& source)
  : dfa(source.dfa)
  , type(source.type) {}

LexicalAnalyzer::LexicalAnalyzer(const std::vector<DfaAndType>& analyzer)
  : analyzer_(analyzer) {}

std::vector<sangyu::Token>
LexicalAnalyzer::Run(std::fstream& file) {
    std::vector<Token> result;
    while (!file.eof()) {
        bool none_match = true;
        for (decltype(analyzer_.size()) i = 0; i < analyzer_.size(); i++) {
            std::string buffer = analyzer_[i].dfa->Judge(file);
            if (!buffer.empty() && analyzer_[i].type != DfaType::kSpace) {
                none_match = false;
                // std::cout << buffer << std::endl;
                // if (analyzer_[i].type == DfaType::kNum) {
                result.push_back(Token(buffer, kInt));
                // } else if (analyzer_[i].type == DfaType::kPunctuation ||
                //  analyzer_[i].type == DfaType::kKeyword) {
                // result.push_back(Token(buffer, kNum));
                // }
            }
        }
        if (none_match) {
            char c = file.get();
        }
    }
    return result;
}

} // namespace sangyu