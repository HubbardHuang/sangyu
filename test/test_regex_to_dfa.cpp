#include <iostream>
#include <vector>

#include "dfa.h"
#include "nfa.h"
#include "postfix_regex.h"
#include "preprocessed_regex.h"
#include "test_regex_to_dfa.h"

namespace sangyu {

void
TestRegexToDfa(const std::string& regex, std::ostream& os) {
    os << "**************TestRegexToDfa Start**************" << std::endl;
    PreprocessedRegex preprocessed(regex);
    preprocessed.Test(os);
    os << "-----------------------------------" << std::endl;
    PostfixRegex postfix(preprocessed);
    postfix.Test(os);
    os << "-----------------------------------" << std::endl;
    NFA nfa(postfix);
    nfa.Test(os);
    os << "-----------------------------------" << std::endl;
    DFA dfa(nfa);
    dfa.Test(os);
    os << "**************TestRegexToDfa End**************" << std::endl;
}

void
TestRegexMatch(const std::string& regex, const std::string& str,
               std::ostream& os) {
    DFA dfa(regex, false);
    os << "Regex: " << regex << std::endl;
    os << "String: " << str << std::endl;
    if (dfa.Judge(str)) {
        os << "Succeeded to match." << std::endl;
    } else {
        os << "Failed to match." << std::endl;
    }
}

} // namespace sangyu