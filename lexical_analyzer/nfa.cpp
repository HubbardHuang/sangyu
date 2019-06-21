#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

#include "nfa.h"
#include "postfix_regex.h"

namespace sangyu {

NFA::NFA(const PostfixRegex& source)
  : state_num_max_(-1) {
    std::stack<StatePair> state_pair_stack;
    std::string postfix_regex = source.GetValue();
    unit_type prev_operator = 0;
    for (auto ch : postfix_regex) {
        if (IsValidOperator(ch)) {
            if (state_pair_stack.empty()) {
                continue;
            }
            if (ch == kJoinOperator_) {
                StatePair sp1, sp2;
                sp1 = state_pair_stack.top();
                state_pair_stack.pop();
                sp2 = state_pair_stack.top();
                state_pair_stack.pop();
                // TODO: Optimize the if-else code block
                if (sp1.first - sp2.second == 1) {
                    DeleteOneVertex(sp1);
                    end_state_ = sp1.second; // Update the end state
                    start_state_ = sp2.first;
                } else {
                    AddIntoGraph(StatePair(sp2.second, sp1.first), kEpsilon);
                    end_state_ = sp1.second; // Update the end state
                    start_state_ = sp2.first;
                }
                // state_pair_stack.push(StatePair(sp1.first, sp2.second));
                state_pair_stack.push(StatePair(sp2.first, sp1.second));
            } else if (ch == kOrOperator_) {
                if (prev_operator != kOrOperator_) {
                    StatePair sp1, sp2;
                    sp1 = state_pair_stack.top();
                    state_pair_stack.pop();
                    sp2 = state_pair_stack.top();
                    state_pair_stack.pop();
                    StatePair new_sp;
                    new_sp.first = AssignVertex();
                    new_sp.second = AssignVertex();
                    AddIntoGraph(StatePair(new_sp.first, sp1.first), kEpsilon);
                    AddIntoGraph(StatePair(new_sp.first, sp2.first), kEpsilon);
                    AddIntoGraph(StatePair(sp1.second, new_sp.second),
                                 kEpsilon);
                    AddIntoGraph(StatePair(sp2.second, new_sp.second),
                                 kEpsilon);
                    // Update the start and end state
                    start_state_ = new_sp.first;
                    end_state_ = new_sp.second;
                    state_pair_stack.push(new_sp);
                } else {
                    StatePair master, slave;
                    slave = state_pair_stack.top();
                    state_pair_stack.pop();
                    master = state_pair_stack.top();
                    state_pair_stack.pop();
                    AddIntoGraph(StatePair(master.first, slave.first),
                                 kEpsilon);
                    AddIntoGraph(StatePair(slave.second, master.second),
                                 kEpsilon);
                    state_pair_stack.push(master);
                }
            } else if (ch == kClosureOperator_) {
                StatePair sp = state_pair_stack.top();
                state_pair_stack.pop();
                StatePair new_sp;
                new_sp.first = AssignVertex();
                new_sp.second = AssignVertex();
                AddIntoGraph(StatePair(new_sp.first, new_sp.second), kEpsilon);
                AddIntoGraph(StatePair(new_sp.first, sp.first), kEpsilon);
                AddIntoGraph(StatePair(sp.second, new_sp.second), kEpsilon);
                AddIntoGraph(StatePair(sp.second, sp.first), kEpsilon);
                // Update the start and end state
                start_state_ = new_sp.first;
                end_state_ = new_sp.second;

                state_pair_stack.push(new_sp);
            }
            prev_operator = ch;
        } else {
            StatePair sp;
            sp.first = AssignVertex();
            sp.second = AssignVertex();
            Symbol sbl = ch;
            symbols_.insert(sbl);
            AddIntoGraph(sp, sbl);

            // Update the start and end state
            if (state_pair_stack.empty()) {
                start_state_ = sp.first;
            }
            end_state_ = sp.second;

            state_pair_stack.push(sp);
        }
    }

    // Initialize [nfa_] with [nfa_buffer_]
    nfa_ = std::vector<std::map<Symbol, std::set<State>>>(state_num_max_ + 1);
    for (auto sp_w : nfa_buffer_) {
        StatePair sp = sp_w.first;
        Symbol sbl = sp_w.second;
        nfa_[sp.first][sbl].insert(sp.second);
    }
    // Find epsilon closure of each state for DFA conversion
    epsilon_closure_.resize(state_num_max_ + 1);
    for (int i = 0; i <= state_num_max_; i++) {
        epsilon_closure_[i] = FindClosure(i, kEpsilon);
    }
}

NFA::State
NFA::AssignVertex(void) {
    return ++state_num_max_;
}

void
NFA::DeleteOneVertex(NFA::StatePair& sp) {
    // Merge "a -> x" and "x -> b" into "a -> b"
    auto target =
      nfa_buffer_.find(StatePair(state_num_max_ - 1, state_num_max_));
    --state_num_max_;
    Symbol sbl = target->second;
    sp = { state_num_max_ - 1, state_num_max_ };
    nfa_buffer_.erase(target);
    nfa_buffer_.insert({ sp, sbl });
}

void
NFA::AddIntoGraph(const StatePair& sp, const Symbol& sbl) {
    nfa_buffer_.insert({ sp, sbl });
}

std::set<NFA::State>
NFA::FindClosure(const State& start, const Symbol& sbl) {
    std::set<State> closure;
    std::queue<State> state_queue;
    state_queue.push(start);
    while (!state_queue.empty()) {
        State curr = state_queue.front();
        state_queue.pop();
        auto target_ws = nfa_[curr].find(sbl);
        if (target_ws != nfa_[curr].end()) {
            for (auto i : target_ws->second) {
                if (closure.find(i) == closure.end()) {
                    state_queue.push(i);
                    closure.insert(i);
                }
            }
        }
    }
    closure.insert(start);
    return closure;
}

std::vector<std::vector<int>>
NFA::Print(void) {
    std::vector<std::vector<int>> result;
    for (int i = 0; i < nfa_.size(); i++) {
        for (auto ws : nfa_[i]) {
            for (auto s : ws.second) {
                std::vector<int> buffer;
                buffer.push_back(i);
                if (ws.first == kEpsilon) {
                    buffer.push_back('#');
                } else {
                    buffer.push_back(ws.first);
                }
                buffer.push_back(s);
                result.push_back(buffer);
            }
        }
    }
    {
        std::vector<int> buffer;
        for (auto ch : symbols_) {
            buffer.push_back(ch);
        }
        result.push_back(buffer);
    }
    result.push_back({ start_state_, end_state_ });
    return result;
}

const NFA::State&
NFA::GetStartVertex(void) const {
    return start_state_;
}

const NFA::State&
NFA::GetEndVertex(void) const {
    return end_state_;
}

const NFA::State&
NFA::GetVertexMax(void) const {
    return state_num_max_;
}

const NFA::Graph&
NFA::GetGraph(void) const {
    return nfa_;
}

const std::set<NFA::Symbol>&
NFA::GetLables(void) const {
    return symbols_;
}

const std::vector<std::set<NFA::State>>&
NFA::GetEpsilonClosure(void) const {
    return epsilon_closure_;
}

} // namespace sangyu