#ifndef NFA_H
#define NFA_H

#include <bitset>
#include <map>
#include <set>
#include <vector>

#include "regex_definition.h"

namespace sangyu {

class PostfixRegex;

class NFA : public RegexDefinition {
private:
    enum { kWeightTypes = kContentTypes };
    using Vertex = int;
    using VertexPair = std::pair<Vertex, Vertex>;
    using Weight = unit_type;
    std::map<VertexPair, Weight> graph_;
    std::vector<std::map<Weight, std::set<Vertex>>> nfa_;
    Vertex vertex_max;
    Vertex start_vertex_;
    Vertex end_vertex_;
    std::set<Weight> labels_;

private:
    Vertex AssignVertex(void);
    void DeleteOneVertex(VertexPair& vp);
    void AddIntoGraph(const VertexPair& vp, const Weight& w);

public:
    explicit NFA(const PostfixRegex& source);
    ~NFA() = default;

public:
    std::vector<std::vector<int>> Print(void);

private:
    NFA() = delete;
    NFA(const NFA&) = delete;
    NFA(NFA&&) = delete;
    void operator=(const NFA&) = delete;
    void operator=(NFA&&) = delete;
};

} // namespace sangyu

#endif