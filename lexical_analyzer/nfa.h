#ifndef NFA_H
#define NFA_H

#include <bitset>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "finite_automata.h"

namespace sangyu {

class PostfixRegex;

class NFA : public FiniteAutomata {
private:
    enum { kSymbolTypes = kContentTypes };
    using State = NfaState;
    using StatePair = std::pair<State /*start*/, State /*end*/>;
    using Graph = NfaGraph;
    std::map<StatePair, Symbol> nfa_buffer_;
    Graph nfa_;
    State state_num_max_;
    State start_state_;
    State end_state_;
    std::vector<std::set<State>> epsilon_closure_;

private:
    State AssignVertex(void);
    void DeleteOneVertex(StatePair& sp);
    void AddIntoGraph(const StatePair& sp, const Symbol& sbl);

public:
    explicit NFA(const PostfixRegex& source);
    ~NFA() = default;

public:
    std::set<State> FindClosure(const State& start, const Symbol& sbl);

public:
    const State& GetStartVertex(void) const;
    const State& GetVertexMax(void) const;
    const State& GetEndVertex(void) const;
    const Graph& GetGraph(void) const;
    const std::set<Symbol>& GetLables(void) const;
    const std::vector<std::set<State>>& GetEpsilonClosure(void) const;
    void Test(std::ostream& os = std::cout);

private:
    NFA() = delete;
    NFA(const NFA&) = delete;
    NFA(NFA&&) = delete;
    void operator=(const NFA&) = delete;
    void operator=(NFA&&) = delete;
};

} // namespace sangyu

#endif