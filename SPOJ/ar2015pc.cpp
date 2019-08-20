#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>
#include <array>
#include <unordered_set>

using namespace std;


using Index = int;
using Count = int;

template<class NodeType, class EdgeType>
class DirEdgedGraphBuilder;

template<class NodeType, class EdgeType>
class UndirEdgedGraphBuilder;

// we are providing something like interface

// this class is going to be used both, by directed graphs and undirected graphs.
// the difference is only in how you build it.
template<class T>
class Graph {
public:
    // somewhere should be typename
    using NodeType = T;

protected:
    std::vector<std::vector<NodeType>> nextNodes_;

public:
    const std::vector<NodeType>& nextNodes(NodeType n) const {
        return nextNodes_[n];
    }

    Count nodeCount() const {
        return nextNodes_.size();
    }

    Graph<T> reversed() const {
        Graph<T> rG;
        rG.nextNodes_.resize(nodeCount());
        for (int i = 0; i < nodeCount(); ++i) {
            for (auto j : nextNodes(i)) {
                rG.nextNodes_[j].push_back(i);
            }
        }
        return rG;
    }


    template<class NodeType, class EdgeType>
    friend class DirEdgedGraphBuilder;
    template<class NodeType, class EdgeType>
    friend class UndirEdgedGraphBuilder;

};

template<class T, class E>
class EdgedGraph : public Graph<T> {
public:

    using NodeType = T;
    using EdgeType = E;

    using Graph<T>::nextNodes;
    using Graph<T>::nodeCount;

protected:
    std::vector<std::vector<EdgeType>> nextEdges_;
    int edgeCount_;

public:
    const std::vector<EdgeType>& nextEdges(NodeType n) const {
        return nextEdges_[n];
    }

    Count edgeCount() const {
        return edgeCount_;
    }

    EdgedGraph<T, E> reversed() const {
        EdgedGraph<T, E> rEG;
        rEG.nextNodes_.resize(nodeCount());
        rEG.nextEdges_.resize(nodeCount());
        for (int i = 0; i < nodeCount(); ++i) {
            for (auto p : nextPairs(i)) {
                rEG.nextNodes_[p.node].push_back(i);
                rEG.nextEdges_[p.node].push_back(p.edge);
            }
        }
        return rEG;
    }

    struct Pair {
        NodeType node;
        EdgeType edge;
    };

    using V_IT = typename std::vector<NodeType>::const_iterator;
    using D_IT = typename std::vector<EdgeType>::const_iterator;

    struct Iterator : public std::iterator<std::random_access_iterator_tag, Pair> {

        Iterator(V_IT vIt, D_IT dIt)
            : vIt(vIt), dIt(dIt) {}

        bool operator<(const Iterator it) const {
            return vIt < it.vIt;
        }

        bool operator!=(const Iterator it) const {
            return vIt != it.vIt;
        }

        Iterator& operator+=(Count count) {
            vIt += count;
            dIt += count;
        }

        Iterator& operator-=(Count count) {
            vIt -= count;
            dIt -= count;
        }

        Iterator& operator++() {
            ++vIt;
            ++dIt;
            return *this;
        }

        Pair operator*() {
            return {*vIt, *dIt};
        }

    private:
        V_IT vIt;
        D_IT dIt;
    };

    // should better use const
    struct S {
        S(const std::vector<NodeType>& vs, const std::vector<EdgeType>& ds)
            : vs(&vs), ds(&ds) {}

        Iterator begin() {
            return Iterator(vs->begin(), ds->begin());
        }

        Iterator end() {
            return Iterator(vs->end(), ds->end());
        }

        const std::vector<NodeType>* vs;
        const std::vector<EdgeType>* ds;
    };

    S nextPairs(NodeType i) const {
        return S(nextNodes(i), nextEdges(i));
    }

    friend class DirEdgedGraphBuilder<NodeType, EdgeType>;
    friend class UndirEdgedGraphBuilder<NodeType, EdgeType>;
};


template<class NodeType, class EdgeType>
class DirEdgedGraphBuilder {
protected:
    Index newEdge = 0;
    EdgedGraph<NodeType, EdgeType> g_;

public:
    DirEdgedGraphBuilder(Count nodeCount) {
        g_.nextNodes_.resize(nodeCount);
        g_.nextEdges_.resize(nodeCount);
    }

    virtual EdgeType add(NodeType from, NodeType to) {
        g_.nextNodes_[from].push_back(to);
        g_.nextEdges_[from].push_back(newEdge);
        return newEdge++;
    }

    EdgedGraph<NodeType, EdgeType> build() {
        g_.edgeCount_ = newEdge;
        return std::move(g_);
    }
};


template<class NodeType, class EdgeType>
class UndirEdgedGraphBuilder : DirEdgedGraphBuilder<NodeType, EdgeType> {

    using DirEdgedGraphBuilder<NodeType, EdgeType>::g_;
    using DirEdgedGraphBuilder<NodeType, EdgeType>::newEdge;
public:

    using DirEdgedGraphBuilder<NodeType, EdgeType>::build;
    using DirEdgedGraphBuilder<NodeType, EdgeType>::DirEdgedGraphBuilder;
    // use constructor of base class

    virtual EdgeType add(NodeType from, NodeType to) {
        g_.nextNodes_[from].push_back(to);
        g_.nextNodes_[to].push_back(from);
        g_.nextEdges_[from].push_back(newEdge);
        g_.nextEdges_[to].push_back(newEdge);
        return newEdge++;
    }

    friend class Graph<NodeType>;
    friend class EdgedGraph<NodeType, EdgeType>;
};


class DisjointSet {
public:
    DisjointSet() {}
    DisjointSet(Count element_count) {
        Init(element_count);
    }

    void Init(Count element_count) {
        set_count_ = element_count;
        data_.resize(element_count);
        size_.resize(element_count);
        Reset();
    }

    void Reset() {
        for (auto i = 0; i < data_.size(); ++i) data_[i] = i;
        fill(size_.begin(), size_.end(), 1);
    }

    void Unite(Index i_0, Index i_1) {
        auto r_0 = root(i_0);
        auto r_1 = root(i_1);
        if (r_0 == r_1) return;
        --set_count_;
        // will join r_0 to r_1, so r_1 height should be bigger
        if (size_[r_0] > size_[r_1]) {
            std::swap(r_0, r_1);
        }
        data_[r_0] = r_1;
        size_[r_1] += size_[r_0];

    }

    Index Add() {
        Count sz = data_.size();
        data_.resize(sz + 1);
        size_.resize(sz + 1);
        data_.back() = sz;
        size_.back() = 1;
        ++set_count_;
        return sz;
    }

    bool is_separate(Index i_0, Index i_1) {
        return root(i_0) != root(i_1);
    }

    Index root(Index i) {
        while (i != data_[i]) {
            i = data_[i] = data_[data_[i]];
        }
        return i;
    }

    size_t size() const {
        return data_.size();
    }

    size_t root_size(Index i) {
        return size_[root(i)];
    }

    Count set_count() {
        return set_count_;
    }

private:
    Count set_count_;
    std::vector<Index> data_;
    // how many elements in set with index, if index is root
    std::vector<size_t> size_;
};


void DecreaseClustering(std::vector<Index>& belong, const std::vector<bool>& res) {
    std::vector<Count> ds(res.size(), 0);
    auto diff = 0;
    for (auto i = 0; i < res.size(); ++i) {
        ds[i] = diff;
        if (!res[i]) ++diff;
    }
    for (auto& b : belong) {
        if (!res[b]) b = -1;
        else {
            b -= ds[b];
        }
    }
}


enum class BFS_Flow {
    // don't expand on children
        Skip,
    Continue,
    Terminate
};

// sometimes it's important for you to have previous vertex
// but here we don't process initial vertex because it has no previous one
template<class Process, class Graph>
void BFS_Prev(const Graph& gr, Index v, Process&& pr) {
    std::queue<Index> q;
    Count c = gr.nodeCount();
    std::vector<bool> visited(c, false);
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        // should we also pass from where we came from
        for (Index w : gr.nextNodes(v)) {
            if (!visited[w]) {
                BFS_Flow flow = pr(w, v);
                if (flow == BFS_Flow::Terminate) return;
                visited[w] = true;
                if (flow == BFS_Flow::Skip) continue;
                q.push(w);
            }
        }
    }
}


struct PartitionResult {
    std::vector<Index> node_partition;
    std::vector<Count> node_degree;
};


// node -> cluster
inline PartitionResult Partition(const Graph<Index>& graph) {
    DisjointSet set(graph.nodeCount());
    std::vector<Count> degrees(graph.nodeCount());
    for (auto n = 0; n < graph.nodeCount(); ++n) {
        degrees[n] = graph.nextNodes(n).size();
    }
    // connect all rays
    for (auto n = 0; n < graph.nodeCount(); ++n) {
        Index p = n;
        // could be done by BFS too
        while (degrees[p] == 1) {
            auto& ns = graph.nextNodes(p);
            auto k = *std::find_if(ns.begin(), ns.end(), [&](auto k) { return set.is_separate(k, p); });
            set.Unite(k, p);
            --degrees[k];
            --degrees[p];
            p = k;
        }
    }

    std::vector<Index> degree_nodes;
    for (auto n = 0; n < graph.nodeCount(); ++n) {
        if (degrees[n] == 2) {
            BFS_Prev(graph, n, [&](auto to, auto from) {
                if (!set.is_separate(to, from)) return BFS_Flow::Skip;
                if (degrees[to] > 2) return BFS_Flow::Skip;

                degree_nodes.clear();
                for (auto n : graph.nextNodes(to)) {
                    if (set.is_separate(to, n)) degree_nodes.push_back(n);
                }

                if (degree_nodes.size() == 2 && !set.is_separate(degree_nodes[0], degree_nodes[1])) {
                    --degrees[degree_nodes[0]];
                    --degrees[degree_nodes[1]];
                    --degrees[to];
                    --degrees[to];
                } else {
                    --degrees[to];
                    --degrees[from];
                }
                set.Unite(to, from);

                return BFS_Flow::Continue;
            });
        }
    }

    // now only roots left and we should consolidate the findings

    std::vector<Index> set_roots(graph.nodeCount());
    std::vector<bool> exists(graph.nodeCount(), false);
    for (auto n = 0; n < graph.nodeCount(); ++n) {
        set_roots[n] = set.root(n);
        exists[set_roots[n]] = true;
    }
    DecreaseClustering(set_roots, exists);

    return PartitionResult{std::move(set_roots), std::move(degrees)};
};


template <typename T_Dist>
class Partition_SP {

    using Node = Index;

    // don't need to keep it here, use another struct
    const EdgedGraph<Index, Index>& graph;
    const std::vector<T_Dist>& edge_dist;

    struct Sole {};

    struct Segment {
        std::array<Node, 2> ends;
        T_Dist dist = std::numeric_limits<T_Dist>::max();

        Node& another(Node end) {
            return end == ends[0] ? ends[1] : ends[0];
        }

        Node& get(Node end) {
            return end == ends[0] ? ends[0] : ends[1];
        }
    };

    struct Root {
        Node origin;
    };

    // node -> unit
    std::vector<Index> nodes_unit;
    // unit -> nodes
    std::vector<std::vector<Node>> unit_nodes;


    enum class UnitType {
        Segment,
        Sole,
        Root
    };

    struct Unit {
        UnitType unit_type;
        Index index;
    };

    std::vector<Segment> segments;
    std::vector<Root> roots;
    Sole sole;

    std::vector<Unit> units;

    struct ProgressItem {
        Node to;
        Node from;
        T_Dist dist;

        ProgressItem() = default;
        ProgressItem(Node to, Node from, T_Dist dist)
            : to(to), from(from), dist(dist) {}

        bool operator<(const ProgressItem& item) const {
            return dist > item.dist;
        }
    };

    std::priority_queue<ProgressItem> queue;

    Node target;
    T_Dist target_dist;

    bool stop_search;

    std::vector<T_Dist> reach;
    std::unordered_set<Index> reach_reset;

public:
    Partition_SP(const EdgedGraph<Index, Index>& graph, const std::vector<T_Dist>& edge_dist)
        : graph(graph), edge_dist(edge_dist), reach(graph.nodeCount(), std::numeric_limits<T_Dist>::max()) {

        auto res = Partition(graph);
        auto& set_roots = res.node_partition;
        auto& degrees = res.node_degree;

        auto set_count = *std::max_element(set_roots.begin(), set_roots.end()) + 1;

        unit_nodes.clear();
        unit_nodes.resize(set_count);
        for (auto n = 0; n < graph.nodeCount(); ++n) {
            unit_nodes[set_roots[n]].push_back(n);
        }

        units.resize(set_count);
        nodes_unit.resize(graph.nodeCount());

        // allow FindSameUnit to work for Segment init
        for (auto i = 0; i < unit_nodes.size(); ++i) {
            for (auto n : unit_nodes[i]) {
                nodes_unit[n] = i;
            }
        }

        for (auto i = 0; i < unit_nodes.size(); ++i) {
            std::vector<Node> degree_nodes;
            for (auto n : unit_nodes[i]) {
                if (degrees[n] != 0) degree_nodes.push_back(n);
            }

            switch (degree_nodes.size()) {
                case 0: {
                    units[i] = {UnitType::Sole, -1};
                    break;
                }

                case 1: {
                    units[i] = {UnitType::Root, static_cast<Index>(roots.size())};
                    roots.push_back(Root{degree_nodes[0]});
                    break;
                }
                case 2: {
                    units[i] = {UnitType::Segment, static_cast<Index>(segments.size())};
                    reach[degree_nodes[0]] = 0;
                    segments.push_back(Segment{{degree_nodes[0], degree_nodes[1]},
                                               FindSameUnit(degree_nodes[0], degree_nodes[1])});
                    ResetUnitReach(nodes_unit[degree_nodes[0]]);
                    break;
                }

                default: throw std::runtime_error("corrupted state");
            }
        }
    }

    T_Dist Query(Node source, Node target) {
        this->target = target;
        target_dist = std::numeric_limits<T_Dist>::max();

        stop_search = false;

        queue = std::priority_queue<ProgressItem>();
        reach_reset.clear();

        reach[source] = 0;

        auto& item = units[nodes_unit[source]];
        Visit(item, [&](auto& item) { InitProgress(item, source); });

        Run();

        for (auto& u : units) {
            Visit(u, [&](auto& u) { ResetBoundVisited(u); });
        }
        for (auto i : reach_reset) {
            ResetUnitReach(i);
        }


        return target_dist;
    }

private:

    void ResetUnitReach(Index unit_index) {
        for (auto n : unit_nodes[unit_index]) {
            reach[n] = std::numeric_limits<T_Dist>::max();
        }
    }

    template <class Func>
    void Visit(Unit unit, Func&& func) {
        switch (unit.unit_type) {
            case UnitType::Sole: func(sole); break;
            case UnitType::Segment: func(segments[unit.index]); break;
            case UnitType::Root: func(roots[unit.index]); break;
        }
    }

    void ResetBoundVisited(Segment& s) {
        reach[s.ends[0]] = std::numeric_limits<T_Dist>::max();
        reach[s.ends[1]] = std::numeric_limits<T_Dist>::max();

    }

    void ResetBoundVisited(Root& s) {
        reach[s.origin] = std::numeric_limits<T_Dist>::max();
    }

    void ResetBoundVisited(Sole&) {}

    // may need to know distance
    T_Dist FindSameUnit(Node source, Node target) {
        reach_reset.insert(nodes_unit[source]);

        std::queue<ProgressItem> q;
        q.emplace(source, -1, reach[source]);

        while (!q.empty()) {
            auto item = q.front();
            q.pop();
            if (reach[item.to] <= item.dist) continue;
            reach[item.to] = item.dist;

            for (auto p : graph.nextPairs(item.to)) {
                if (SameUnit(source, p.node) && p.node != item.from) {
                    q.emplace(p.node, item.to, item.dist + edge_dist[p.edge]);
                }
            }
        }

        return reach[target];
    }

    void InitProgress(Sole& sole, Node source) {
        stop_search = true;
        if (!SameUnit(source, target)) return;

        target_dist = FindSameUnit(source, target);
    }

    void InitProgress(Root& root, Node source) {
        if (SameUnit(source, target)) {
            target_dist = FindSameUnit(source, target);
            stop_search = true;
            return;
        }

        auto dist = FindSameUnit(source, root.origin);

        ForBoundNodes(root.origin, [&](auto node, auto edge) {
            queue.emplace(node, root.origin, dist + edge_dist[edge]);
        });
    }

    void InitProgress(Segment& segment, Node source) {

        if (SameUnit(source, target)) {
            target_dist = FindSameUnit(source, target);
        }

        for (auto i : {0, 1}) {
            auto dist = FindSameUnit(source, segment.ends[i]);
            ForBoundNodes(segment.ends[i], [&] (auto node, auto edge) {
                PushBound(node, segment.ends[i], dist + edge_dist[edge]);
            });
        }
    }

    void Run() {
        while (!stop_search && !queue.empty()) {
            auto top = queue.top();
            queue.pop();
            if (reach[top.to] <= top.dist || top.dist >= target_dist) break;

            auto& item = units[nodes_unit[top.to]];
            Visit(item, [&](auto& item) {
                BoundProgress(item, top.to, top.dist);
            });
        }
    }

    // Border progress is made straight from the priority queue

    void BoundProgress(Sole&, Node, T_Dist) {}

    void BoundProgress(Root& root, Node, T_Dist cur_dist) {

        if (SameUnit(root.origin, target)) {
            // can leave after that
            target_dist = FindSameUnit(root.origin, target);
            stop_search = true;
            return;
        }

        ForBoundNodes(root.origin, [&] (auto node, auto edge) {
            PushBound(node, root.origin, cur_dist + edge_dist[edge]);
        });
    }

    void BoundProgress(Segment& segment, Node end_node, T_Dist cur_dist) {

        if (SameUnit(end_node, target)) {
            auto to_target = FindSameUnit(end_node, target);
            target_dist = std::min(target_dist, to_target);

            return;
        }

        auto another = segment.another(end_node);
        auto across_dist = segment.dist;

        ForBoundNodes(another, [&] (auto node, auto edge) {
            PushBound(node, another, cur_dist + across_dist + edge_dist[edge]);
        });
    }

    template <typename Func>
    void ForBoundNodes(Node node, Func func) {
        for (auto p : graph.nextPairs(node)) {
            if (SameUnit(p.node, node)) continue;
            func(p.node, p.edge);
        }
    }

    void PushBound(Node to, Node from, T_Dist dist) {
        if (reach[to] <= dist || dist >= target_dist) return;
        queue.emplace(to, from, dist);
    }

    bool SameUnit(Node n_1, Node n_2) const {
        return nodes_unit[n_1] == nodes_unit[n_2];
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N, M, Q;
        cin >> N >> M >> Q;
        UndirEdgedGraphBuilder<Index, Index> builder(N);
        vector<int> edgeValues;
        edgeValues.reserve(M);
        for (int m = 0; m < M; ++m) {
            int U, V, D;
            cin >> U >> V >> D;
            --U; --V;
            edgeValues.push_back(D);
            builder.add(U, V);
        }

        cout << "Case " << t+1 << ":\n";

        auto graph = builder.build();
        Partition_SP<int32_t> pp(graph, edgeValues);

        // graph is way too big
        // special allocation maybe required

        // write tests for the problem
        // try max possible 

        for (auto q = 0; q < Q; ++q) {
            int S, D;
            cin >> S >> D;
            --S; --D;
            int val;
            bool vis;
            val = pp.Query(S, D);
            cout << val << endl;
        }
    }

}
