#include <algorithm>
#include <iostream>
#include <queue>

#include "dfa.h"

namespace sangyu {

DFA::DFA(const NFA& source)
  : state_num_max_(-1) {
    NfaGraph nfa_graph = source.GetGraph();
    NfaState nfa_start_state = source.GetStartVertex();
    NfaState nfa_end_state = source.GetEndVertex();
    std::vector<std::set<NfaState>> epsilon_closure =
      source.GetEpsilonClosure();
    NfaState nfa_state_num_max = source.GetVertexMax();
    symbols_ = source.GetLables();

    std::queue<NfaStateSet> nfa_state_set_queue;
    nfa_state_set_queue.push(epsilon_closure[nfa_start_state]);
    while (!nfa_state_set_queue.empty()) {
        NfaStateSet curr_nfa_state_set = nfa_state_set_queue.front();
        nfa_state_set_queue.pop();
        for (auto sbl : symbols_) {
            NfaStateSet new_nfa_state_set;
            for (auto s : curr_nfa_state_set) {
                auto ev = nfa_graph[s].find(sbl);
                if (ev != nfa_graph[s].end()) {
                    for (auto target : ev->second) {
                        for (auto v : epsilon_closure[target]) {
                            new_nfa_state_set.insert(v);
                        }
                    }
                }
            }
            if (new_nfa_state_set.empty()) {
                continue;
            }
            bool is_non_empty_subset =
              IsNonEmptySubset(new_nfa_state_set, curr_nfa_state_set);
            bool repeat = (num_of_.find(new_nfa_state_set) != num_of_.end());
            AddIntoGraph(curr_nfa_state_set, sbl, new_nfa_state_set);
            if (!repeat && !is_non_empty_subset) {
                nfa_state_set_queue.push(new_nfa_state_set);
            }
        }
    }

    // Find the start state of [dfa_]
    for (auto item : num_of_) {
        NfaStateSet curr = item.first;
        if (curr.find(nfa_start_state) != curr.end()) {
            start_state_ = item.second;
            break;
        }
    }
    // Find the end states of [dfa_]
    // and there may be more than one end states in a DFA
    for (auto item : num_of_) {
        NfaStateSet curr = item.first;
        if (curr.find(nfa_end_state) != curr.end()) {
            end_state_.insert(item.second);
        }
    }
}

bool
DFA::IsNonEmptySubset(DFA::NfaStateSet left, DFA::NfaStateSet right) {
    if (left.size() > right.size()) {
        std::swap(left, right);
    }
    // There must be left.size() <= right.size()
    if (left.empty()) {
        return false;
    }
    int original_length = right.size();
    for (auto l : left) {
        right.insert(l);
        if (right.size() != original_length) {
            return false;
        }
    }
    return true;
}

void
DFA::AssginStateNumber(const NfaStateSet& n) {
    num_of_[n] = ++state_num_max_;
}

void
DFA::AddIntoGraph(const NfaStateSet& start, const Symbol& symbol,
                  const NfaStateSet& end) {
    if (num_of_.find(start) == num_of_.end()) {
        AssginStateNumber(start);
    }
    if (num_of_.find(end) == num_of_.end()) {
        AssginStateNumber(end);
    }
    dfa_[num_of_[start]][symbol].insert(num_of_[end]);
}

void
DFA::Test(void) {
    std::cout << "state_set_total = " << state_num_max_ << std::endl;
    std::cout << "Number of state set: " << std::endl;
    for (auto p : num_of_) {
        std::cout << '[';
        std::cout << p.second;
        std::cout << "]: ";
        std::cout << "{ ";
        for (auto v : p.first) {
            std::cout << v << " ";
        }
        std::cout << "}";
        std::cout << std::endl;
    }
    std::cout << "DFA:" << std::endl;
    for (auto v1_e_v2 : dfa_) {
        for (auto e_v2 : v1_e_v2.second) {
            for (auto target : e_v2.second) {
                std::cout << "{ " << v1_e_v2.first << " " << e_v2.first << " "
                          << target << " }" << std::endl;
            }
        }
    }
}

} // namespace sangyu