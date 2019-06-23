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
    // std::string re_space = "\\s*(\\p|\\d\\l)";
    std::string re_space = "\\s*";
    std::string re_look_forward = "(\\p|\\s)";
    // std::string re_id = "(_|\\l)(_|\\l|\\d)*" + re_look_forward;
    std::string re_id = "(_|\\l)(_|\\l|\\d)*";
    std::string re_keyword =
      "(int|char|const|include|void|return)" + re_look_forward;
    // std::string re_punct = "(=|<|>|;|{|}|\\(|\\)|,)(\\s|\\d|\\l)";
    std::string re_punct = "(=|<|>|;|{|}|\\(|\\)|,)|\\*|[|]|#";
    // std::string re_punct = "\\(|\\)|,";
    // std::string re_comment1 = "(/\\*(\\d|\\l|\\s)*\\*/)";
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

    sangyu::DfaAndType dfa_space(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_space, false)),
      sangyu::DfaType::kSpace);
    sangyu::DfaAndType dfa_id(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_id, false)),
      sangyu::DfaType::kId);
    sangyu::DfaAndType dfa_punct(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_punct, false)),
      sangyu::DfaType::kPunctuation);
    sangyu::DfaAndType dfa_keyword(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_keyword, true)),
      sangyu::DfaType::kKeyword);
    sangyu::DfaAndType dfa_num(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_num, false)),
      sangyu::DfaType::kNum);
    sangyu::DfaAndType dfa_comment2(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_comment2, true)),
      sangyu::DfaType::kComment);
    sangyu::DfaAndType dfa_constchar(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_constchar, false)),
      sangyu::DfaType::kCharacterLiteral);
    sangyu::DfaAndType dfa_conststr(
      std::shared_ptr<sangyu::DFA>(new sangyu::DFA(re_conststr, false)),
      sangyu::DfaType::kStringLiteral);

    std::vector<sangyu::DfaAndType> dfa{ dfa_space,     dfa_id,
                                         dfa_punct,     dfa_keyword,
                                         dfa_num,       dfa_comment2,
                                         dfa_constchar, dfa_conststr };

    std::fstream file("/home/hhb/practice/sangyu/code.c.test");
    sangyu::LexicalAnalyzer la(dfa);
    std::vector<sangyu::Token> tokens = la.Run(file);
    for (auto t : tokens) {
        std::cout << t.name << std::endl;
    }
    file.close();

    return 0;
}