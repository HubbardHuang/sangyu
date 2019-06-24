#include <iostream>

#include "lexical_analyzer.h"

namespace sangyu {

const Token::Type Token::kNum = "num";
const Token::Type Token::kId = "id";
const Token::Type Token::kLtrChar = "charl";
const Token::Type Token::kLtrStr = "strl";
const Token::Type Token::kComment = "comment";

Token::Token(const std::string& n, const Token::Type& t)
  : name(n)
  , type(t) {}

Token::Token(const Token& source)
  : name(source.name)
  , type(source.type) {}

LexicalAnalyzer::LexicalAnalyzer(
  const std::vector<std::pair<std::shared_ptr<DFA>, DfaType>>& analyzer)
  : analyzer_(analyzer.size()) {
    for (auto a : analyzer) {
        analyzer_[a.second] = a.first;
    }
}

std::vector<sangyu::Token>
LexicalAnalyzer::Run(std::fstream& file, std::ostream& os) {
    std::vector<Token> result;
    while (!file.eof()) {
        bool none_match = true;
        for (decltype(analyzer_.size()) i = 0; i < analyzer_.size(); i++) {
            std::string buffer = analyzer_[i]->Judge(file);
            if (!buffer.empty() && i != kSpaceDfa) {
                none_match = false;
                Token::Type token_type;
                switch (i) {
                case kPunctuationDfa:
                case kKeywordDfa:
                    token_type = buffer;
                    break;
                case kNumDfa:
                    token_type = Token::kNum;
                    break;
                case kIdDfa:
                    // Check if a keyword is misjudged as an id
                    if (analyzer_[kKeywordDfa]->Judge(file).empty()) {
                        token_type = Token::kId;
                    } else { // Not misjudged
                        token_type = buffer;
                    }
                    break;
                case kCharacterLiteralDfa:
                    token_type = Token::kLtrStr;
                    break;
                case kStringLiteralDfa:
                    token_type = Token::kLtrStr;
                    break;
                case kCommentDfa:
                    token_type = Token::kComment;
                    break;
                default:
                    break;
                }
                if (token_type != Token::kComment) {
                    result.push_back(Token(buffer, token_type));
                }
            }
        }
        if (none_match) {
            char c = file.get();
            none_match = false;
            // Error
            os << "Unrecognized symbol " << c << "." << std::endl;
            return {};
        }
    }
    return result;
}

} // namespace sangyu