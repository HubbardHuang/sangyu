#include <iostream>
#include <string>

#include "postfix_regex.h"
#include "prefix_regex.h"

int
main(int argc, char** argv) {
    std::string regex = "(ab|c)*de";
    sangyu::PrefixRegex prefix(regex);
    std::string prefix_value = prefix.GetValue();
    for (auto c : prefix_value) {
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
    sangyu::PostfixRegex postfix(prefix);
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
    return 0;
}