#ifndef DFA_H
#define DFA_H

#include <map>

#include "finite_automata.h"
#include "nfa.h"

namespace sangyu {

class DFA : public FiniteAutomata {
private:
    using Graph = DfaGraph;
    DfaState state_num_max_;
    Graph dfa_;
    std::map<NfaStateSet, DfaState> num_of_;
    DfaState start_state_;
    std::set<DfaState> end_state_;

private:
    bool IsNonEmptySubset(NfaStateSet left, NfaStateSet right);
    void AssginStateNumber(const NfaStateSet& n);
    void AddIntoGraph(const NfaStateSet& start, const Symbol& symbol,
                      const NfaStateSet& end);

public:
    explicit DFA(const NFA& source);
    ~DFA() = default;

public:
    void Test(void);
    bool Judge(const std::string& str);

private:
    DFA() = delete;
    DFA(const DFA&) = delete;
    DFA(DFA&&) = delete;
    void operator=(const DFA&) = delete;
    void operator=(DFA&&) = delete;
};

} // namespace sangyu

#endif