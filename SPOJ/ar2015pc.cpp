
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>

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


template<class EdgedGraph, class Value>
class DijkstraShortestPath {
    
    struct Item {
        Index dst;
        Value val;
        
        Item(Index dst, Value val) 
        : dst(dst), val(val) {}
        
        bool operator<(const Item& t) const {
            // need min priority queue
            return val > t.val;
        }
    };
    
public:
    DijkstraShortestPath(const EdgedGraph& graph, const std::vector<Value>& edgeValues) 
    : graph(graph), edgeValues(edgeValues), vis(graph.nodeCount()), res(graph.nodeCount()) {
        
        vis2[0].resize(graph.nodeCount());
        vis2[1].resize(graph.nodeCount());
    }
    
    // for each how much to travel
    // could return ref, and keep array for reuse
    // but that way it can be moved to the client actually
    std::tuple<std::vector<Value>, std::vector<bool>> Compute(Index origin) {
        std::vector<bool> visited(graph.nodeCount(), false);
        std::vector<Value> res(graph.nodeCount(), std::numeric_limits<Value>::max());
        res[origin] = 0;
        // by distance put dest
        std::priority_queue<Item> q;
        q.emplace(origin, 0);
        while (!q.empty()) {
            Item t = q.top();
            q.pop();
            if (visited[t.dst]) continue;
            visited[t.dst] = true;
            for (auto p : graph.nextPairs(t.dst)) {
                auto v = t.val + edgeValues[p.edge];
                if (v < res[p.node]) {
                    res[p.node] = v;
                    q.emplace(p.node, v);
                }
            }
        }
        return std::make_tuple(res, visited);
    }
    
    
    std::tuple<Value, bool> Compute(Index src, Index dst) {
        std::fill(vis.begin(), vis.end(), false);
        std::priority_queue<Item> q;
        q.emplace(src, 0);
        while (!q.empty()) {
            auto t = q.top();
            q.pop();
            if (vis[t.dst]) continue;
            if (t.dst == dst) {
                return {t.val, true};
            }
            vis[t.dst] = true;
            for (auto p : graph.nextPairs(t.dst)) {
                if (!vis[p.node]) {
                    q.emplace(p.node, t.val + edgeValues[p.edge]);
                }
            }
        }
        return {0, false};
    }
    
    std::tuple<Value, bool> Compute2(Index src, Index dst) {
        std::fill(vis2[0].begin(), vis2[0].end(), false);
        std::fill(vis2[1].begin(), vis2[1].end(), false);
        
        std::priority_queue<Item> q[2];
        q[0].emplace(src, 0);
        q[1].emplace(dst, 0);
        
        for (;;) {
            auto i = q[0].size() < q[1].size() ? 0 : 1;
            auto t = q[i].top();
            q[i].pop();
            if (vis2[i][t.dst]) continue;
            if (vis2[!i][t.dst]) {
                return make_tuple(res[t.dst] + t.val, true);
            }
            res[t.dst] = t.val;
            vis2[i][t.dst] = true;
            
            for (auto p : graph.nextPairs(t.dst)) {
                if (!vis2[i][p.node]) {
                    q[i].emplace(p.node, t.val + edgeValues[p.edge]);
                }
            }
        }
        return {0, false};
    }
    
    
private:
    const EdgedGraph& graph;
    const std::vector<Value>& edgeValues;
    
    std::vector<bool> vis;
    
    std::vector<bool> vis2[2];
    
    std::vector<Value> res;
};





struct Item {
    Index idx;
    Index src, dst;
    Count d;
    
    Item(Index idx, Index src, Index dst) : idx(idx), src(src), dst(dst) {}
    
    bool operator<(const Item& item) const {
        return src < item.src;
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
        DijkstraShortestPath<decltype(graph), Count> pp(graph, edgeValues);
        
        for (auto q = 0; q < Q; ++q) {
            int S, D;
            cin >> S >> D;
            --S; --D;
            int val;
            bool vis;
            tie(val, vis) = pp.Compute(S, D);
            cout << val << endl;
        }
    }
    
}
