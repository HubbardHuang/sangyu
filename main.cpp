#include <iostream>
#include <string>

#include "dfa.h"
#include "nfa.h"
#include "postfix_regex.h"
#include "preprocessed_regex.h"

int
main(int argc, char** argv) {
    std::string regex = "(ab|c)*de";
    sangyu::PreprocessedRegex preprocessed(regex);
    sangyu::PostfixRegex postfix(preprocessed);
    std::string postfix_value = postfix.GetValue();
    for (auto c : postfix_value) {
        switch (c) {
        case -1:
            std::cout << "(";
            break;
        case -2:
            std::cout << ")";
            break;
        case -3:
            std::cout << "*";
            break;
        case -4:
            std::cout << "|";
            break;
        case -5:
            std::cout << "&";
            break;
        default:
            std::cout << c;
            break;
        }
    }
    std::cout << std::endl;

    sangyu::NFA nfa(postfix);
    std::vector<std::vector<int>> ves = nfa.Print();
    if (ves.empty()) {
        std::cout << "Empty." << std::endl;
        return 0;
    }

    std::vector<int> se(ves.back());
    ves.pop_back();
    std::vector<int> lable(ves.back());
    ves.pop_back();

    for (auto v : ves) {
        std::cout << '{' << ' ';
        std::cout << std::to_string(v[0]) << ", ";
        std::cout << static_cast<char>(v[1]) << ", ";
        std::cout << std::to_string(v[2]) << " ";
        std::cout << '}' << std::endl;
    }
    // std::cout << '{' << ' ';
    // for (auto c : lable) {
    //     std::cout << static_cast<char>(c) << " ";
    // }
    // std::cout << '}' << std::endl;
    // std::cout << "start_vertex: " << se[0] << " ";
    // std::cout << "end_vertex: " << se[1] << std::endl;

    auto sets = nfa.GetEpsilonClosure();
    for (int i = 0; i < sets.size(); i++) {
        std::cout << "vertex " << i << ": ";
        for (auto v : sets[i]) {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------" << std::endl;

    sangyu::DFA dfa(nfa);
    dfa.Test();

    return 0;
}