#ifndef TEST_REGEX_TO_DFA_H
#define TEST_REGEX_TO_DFA_H

#include <iostream>
#include <string>

namespace sangyu {

void TestRegexToDfa(const std::string& regex, std::ostream& os = std::cout);
void TestRegexMatch(const std::string& regex, const std::string& str,
                    std::ostream& os = std::cout);

} // namespace sangyu

#endif