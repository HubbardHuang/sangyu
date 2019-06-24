#include <iostream>
#include <memory>
#include <string>

#include "dfa.h"
#include "lexical_analyzer.h"
#include "nfa.h"
#include "postfix_regex.h"
#include "preprocessed_regex.h"

#include "test_regex_to_dfa.h"

int
main(void) {
    std::string re_space = "\\s*";
    std::string re_look_forward = "(\\p|\\s)";
    std::string re_id = "(_|\\l)(_|\\l|\\d)*";
    std::string re_keyword =
      "(int|char|const|include|void|return)" + re_look_forward;
    std::string re_punct = "(=|<|>|;|{|}|\\(|\\)|,)|\\*|[|]";
    std::string re_comment2 = "(//(\\d|\\l| |\t)*)(\n)";
    std::string re_constchar = "\'(\\u)\'";
    std::string re_conststr = "\"(\\u)*\"";

    std::string digits = "\\d\\d*";
    std::string ee = "(E|e)";
    std::string D1 = digits;
    std::string D2 = digits + "." + digits;
    std::string D3 = D1 + ee + digits;
    std::string D4 = D1 + ee + "+" + digits;
    std::string D5 = D1 + ee + "-" + digits;
    std::string D6 = D2 + ee + digits;
    std::string D7 = D2 + ee + "+" + digits;
    std::string D8 = D2 + ee + "-" + digits;
    std::string re_num = std::string("(") + D1 + "|" + D2 + "|" + D3 + "|" +
                         D4 + "|" + D5 + "|" + D6 + "|" + D7 + "|" + D8 +
                         std::string(")");

    std::shared_ptr<sangyu::DFA> dfa_space(new sangyu::DFA(re_space, false));
    std::shared_ptr<sangyu::DFA> dfa_id(new sangyu::DFA(re_id, false));
    std::shared_ptr<sangyu::DFA> dfa_punct(new sangyu::DFA(re_punct, false));
    std::shared_ptr<sangyu::DFA> dfa_keyword(new sangyu::DFA(re_keyword, true));
    std::shared_ptr<sangyu::DFA> dfa_num(new sangyu::DFA(re_num, false));
    std::shared_ptr<sangyu::DFA> dfa_comment2(
      new sangyu::DFA(re_comment2, true));
    std::shared_ptr<sangyu::DFA> dfa_constchar(
      new sangyu::DFA(re_constchar, false));
    std::shared_ptr<sangyu::DFA> dfa_conststr(
      new sangyu::DFA(re_conststr, false));

    std::vector<std::pair<std::shared_ptr<sangyu::DFA>, sangyu::DfaType>> dfa =
      { { dfa_space, sangyu::kSpaceDfa },
        { dfa_id, sangyu::kIdDfa },
        { dfa_punct, sangyu::kPunctuationDfa },
        { dfa_keyword, sangyu::kKeywordDfa },
        { dfa_num, sangyu::kNumDfa },
        { dfa_comment2, sangyu::kCommentDfa },
        { dfa_constchar, sangyu::kCharacterLiteralDfa },
        { dfa_conststr, sangyu::kStringLiteralDfa } };

    std::fstream file("/home/hhb/practice/sangyu/code.c.test");
    sangyu::LexicalAnalyzer la(dfa);
    std::vector<sangyu::Token> tokens = la.Run(file);
    for (auto t : tokens) {
        std::cout << "[" << t.type << "]\r\t\t" << t.name << std::endl;
    }
    file.close();

    return 0;
}