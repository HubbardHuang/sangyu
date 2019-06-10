#include <iostream>
#include <queue>
#include <string>

#include "nfa.h"
#include "postfix_regex.h"

namespace sangyu {

NFA::NFA(const PostfixRegex& source)
  : vertex_max(-1) {
    std::queue<VertexPair> vertex_pair_queue;
    std::string postfix_regex = source.GetValue();
    for (auto ch : postfix_regex) {
        if (IsValidOperator(ch)) {
            if (vertex_pair_queue.empty()) {
                continue;
            }
            if (ch == kJoinOperator_) {
                VertexPair vp1, vp2;
                vp1 = vertex_pair_queue.front();
                vertex_pair_queue.pop();
                vp2 = vertex_pair_queue.front();
                vertex_pair_queue.pop();
                DeleteOneVertex(vp2);

                // start and end
                end_vertex_ = vp2.second;

                vertex_pair_queue.push(VertexPair(vp1.first, vp2.second));
            } else if (ch == kOrOperator_) {
                VertexPair vp1, vp2;
                vp1 = vertex_pair_queue.front();
                vertex_pair_queue.pop();
                vp2 = vertex_pair_queue.front();
                vertex_pair_queue.pop();
                VertexPair new_vp;
                new_vp.first = AssignVertex();
                new_vp.second = AssignVertex();
                AddIntoGraph(VertexPair(new_vp.first, vp1.first), kEpsilon);
                AddIntoGraph(VertexPair(new_vp.first, vp2.first), kEpsilon);
                AddIntoGraph(VertexPair(vp1.second, new_vp.second), kEpsilon);
                AddIntoGraph(VertexPair(vp2.second, new_vp.second), kEpsilon);
                // start and end
                start_vertex_ = new_vp.first;
                end_vertex_ = new_vp.second;

                vertex_pair_queue.push(new_vp);
            } else if (ch == kClosureOperator_) {
                VertexPair vp = vertex_pair_queue.front();
                vertex_pair_queue.pop();
                VertexPair new_vp;
                new_vp.first = AssignVertex();
                new_vp.second = AssignVertex();
                AddIntoGraph(VertexPair(new_vp.first, new_vp.second), kEpsilon);
                AddIntoGraph(VertexPair(new_vp.first, vp.first), kEpsilon);
                AddIntoGraph(VertexPair(vp.second, new_vp.second), kEpsilon);
                AddIntoGraph(VertexPair(vp.second, vp.first), kEpsilon);
                // start and end
                start_vertex_ = new_vp.first;
                end_vertex_ = new_vp.second;

                vertex_pair_queue.push(new_vp);
            }
        } else {
            VertexPair vp;
            vp.first = AssignVertex();
            vp.second = AssignVertex();
            Weight w = ch;
            labels_.insert(w);
            AddIntoGraph(vp, w);

            // start and end
            if (vertex_pair_queue.empty()) {
                start_vertex_ = vp.first;
            }
            end_vertex_ = vp.second;

            vertex_pair_queue.push(vp);
        }
    }

    // Initialize [nfa_] with [graph_]
    nfa_ = std::vector<std::map<Weight, std::set<Vertex>>>(vertex_max + 1);
    for (auto ve : graph_) {
        VertexPair vp = ve.first;
        Weight w = ve.second;
        nfa_[vp.first][w].insert(vp.second);
    }
}

NFA::Vertex
NFA::AssignVertex(void) {
    return ++vertex_max;
}

void
NFA::DeleteOneVertex(NFA::VertexPair& vp) {
    auto target = graph_.find(VertexPair(vertex_max - 1, vertex_max));
    --vertex_max;
    Weight w = target->second;
    vp = { vertex_max - 1, vertex_max };
    graph_.erase(target);
    graph_.insert({ vp, w });
}

void
NFA::AddIntoGraph(const VertexPair& vp, const Weight& w) {
    graph_.insert({ vp, w });
}

std::vector<std::vector<int>>
NFA::Print(void) {
    std::vector<std::vector<int>> result;
    for (int i = 0; i < nfa_.size(); i++) {
        for (auto ev : nfa_[i]) {
            for (auto v : ev.second) {
                std::vector<int> buffer;
                buffer.push_back(i);
                if (ev.first == kEpsilon) {
                    buffer.push_back('#');
                } else {
                    buffer.push_back(ev.first);
                }
                buffer.push_back(v);
                result.push_back(buffer);
            }
        }
    }
    {
        std::vector<int> buffer;
        for (auto ch : labels_) {
            buffer.push_back(ch);
        }
        result.push_back(buffer);
    }
    { result.push_back({ start_vertex_, end_vertex_ }); }
    return result;
}

} // namespace sangyu