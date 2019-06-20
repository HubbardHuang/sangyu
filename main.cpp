#include <iostream>
#include <string>

#include "dfa.h"
#include "nfa.h"
#include "postfix_regex.h"
#include "preprocessed_regex.h"

int
main(int argc, char** argv) {
    // std::string regex = "d(a|c)*";
    std::string regex = "1()a\\d*\\p*";
    sangyu::PreprocessedRegex preprocessed(regex);
    std::string result = preprocessed.Test();
    // std::cout << result.size() << " " << result << std::endl;
    sangyu::PostfixRegex postfix(preprocessed);
    std::string postfix_value = postfix.Test();
    // std::cout << postfix_value.size() << " " << postfix_value << std::endl;

    sangyu::NFA nfa(postfix);
    // std::vector<std::vector<int>> ves = nfa.Print();
    // if (ves.empty()) {
    //     std::cout << "Empty." << std::endl;
    //     return 0;
    // }

    // std::vector<int> se(ves.back());
    // ves.pop_back();
    // std::vector<int> lable(ves.back());
    // ves.pop_back();

    // for (auto v : ves) {
    //     std::cout << '{' << ' ';
    //     std::cout << std::to_string(v[0]) << ", ";
    //     std::cout << static_cast<char>(v[1]) << ", ";
    //     std::cout << std::to_string(v[2]) << " ";
    //     std::cout << '}' << std::endl;
    // }
    // std::cout << '{' << ' ';
    // for (auto c : lable) {
    //     std::cout << static_cast<char>(c) << " ";
    // }
    // std::cout << '}' << std::endl;
    // std::cout << "start_vertex: " << se[0] << " ";
    // std::cout << "end_vertex: " << se[1] << std::endl;

    // auto sets = nfa.GetEpsilonClosure();
    // for (int i = 0; i < sets.size(); i++) {
    //     std::cout << "vertex " << i << ": ";
    //     for (auto v : sets[i]) {
    //         std::cout << v << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "--------------------------" << std::endl;

    sangyu::DFA dfa(nfa);
    // dfa.Test();
    if (dfa.Judge("1a123\\n\\f")) {
        std::cout << "Yes." << std::endl;
    } else {
        std::cout << "No." << std::endl;
    }

    return 0;
}