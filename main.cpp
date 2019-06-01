#include <iostream>
#include <string>

#include "regex_preprocessor.h"
#include "regex_to_nfa.h"

int
main(int argc, char** argv) {
    std::string regex = "(ab|c*de";
    sangyu::RegexPreprocessor rp(regex);
    std::string result = rp.Run();
    for (auto c : result) {
        // std::cout << static_cast<int>(c) << " ";
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
    sangyu::RegexNfaConverter rnc(result);
    std::string r2 = rnc.GetResult();
    for (auto c : r2) {
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
    return 0;
}