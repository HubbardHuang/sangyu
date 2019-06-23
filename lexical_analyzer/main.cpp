#include <iostream>
#include <string>

#include "dfa.h"
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

    sangyu::DFA dfa_space(re_space, false);
    sangyu::DFA dfa_id(re_id, false);
    sangyu::DFA dfa_punct(re_punct, false);
    sangyu::DFA dfa_keyword(re_keyword, true);

    sangyu::DFA dfa_num(re_num, false);
    // sangyu::DFA dfa_comment1(re_comment1, false);
    sangyu::DFA dfa_comment2(re_comment2, true);
    sangyu::DFA dfa_constchar(re_constchar, false);
    sangyu::DFA dfa_conststr(re_conststr, false);

    std::fstream file("/home/hhb/practice/sangyu/code.c.test");
    while (!file.eof()) {

        // std::cout << "1" << std::endl;
        // getchar();
        // std::cout << "curr:[" << (int)file.get() << "]." << std::endl;
        // file.seekg(-1, std::fstream::cur);

        for (std::string buffer = dfa_space.Judge(file); !buffer.empty();) {
            std::cout << "space: " << buffer.size() << std::endl;
            // getchar();
            break;
        }
        if (file.eof()) {
            break;
        }

        // std::cout << "2" << std::endl;
        // getchar();
        // std::cout << "curr:[" << (char)file.get() << "]." << std::endl;
        // file.seekg(-1, std::fstream::cur);

        for (std::string buffer = dfa_keyword.Judge(file); !buffer.empty();) {
            std::cout << "keyword: " << buffer << std::endl;
            // getchar();
            break;
        }
        // if (file.eof()) {
        //     break;
        // }

        for (std::string buffer = dfa_id.Judge(file); !buffer.empty();) {
            std::cout << "id: " << buffer << std::endl;
            // getchar();
            break;
        }
        if (file.eof()) {
            break;
        }

        // std::cout << "3" << std::endl;
        // getchar();
        // std::cout << "curr:[" << (char)file.get() << "]." << std::endl;
        // file.seekg(-1, std::fstream::cur);
        for (std::string buffer = dfa_comment2.Judge(file); !buffer.empty();) {
            std::cout << "com2: [" << buffer << "]" << std::endl;
            // getchar();
            break;
        }
        // for (std::string buffer = dfa_comment1.Judge(file);
        // !buffer.empty();)
        // {
        //     std::cout << "com1: [" << buffer << "]" << std::endl;
        //     // getchar();
        //     break;
        // }
        for (std::string buffer = dfa_constchar.Judge(file); !buffer.empty();) {
            std::cout << "con-char: " << buffer << std::endl;
            // getchar();
            break;
        }
        for (std::string buffer = dfa_conststr.Judge(file); !buffer.empty();) {
            std::cout << "con-str: " << buffer << std::endl;
            // getchar();
            break;
        }
        for (std::string buffer = dfa_punct.Judge(file); !buffer.empty();) {
            std::cout << "punct: " << buffer << std::endl;
            // getchar();
            break;
        }
        // if (file.eof()) {
        //     break;
        // }
        for (std::string buffer = dfa_num.Judge(file); !buffer.empty();) {
            std::cout << "num: " << buffer << std::endl;
            // getchar();
            break;
        }
    }
    file.close();

    return 0;
}