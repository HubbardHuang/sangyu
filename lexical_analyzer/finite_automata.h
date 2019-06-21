#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <map>
#include <set>
#include <vector>

#include "regex_definition.h"

namespace sangyu {

class FiniteAutomata : public RegexDefinition {
protected:
    using Symbol = unit_type;
    using NfaState = int;
    using DfaState = int;
    using NfaStateSet = std::set<NfaState>;
    using NfaGraph = std::vector<std::map<Symbol, std::set<NfaState>>>;
    // using DfaGraph = std::map<DfaState, std::map<Symbol,
    // std::set<DfaState>>>;
    using DfaGraph = std::map<DfaState, std::map<Symbol, DfaState>>;

protected:
    std::set<Symbol> symbols_;
};

} // namespace sangyu

#endif