#include <vector>
#include <tuple>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <memory>
#include <algorithm>



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
    
private:    
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

template<class NodeType>
struct DirGraphBuilder {
    
    Graph<NodeType> g_;
    
    DirGraphBuilder(Count nodeCount) {
        g_.nextNodes_.resize(nodeCount);
    }
    
    virtual void add(NodeType from, NodeType to) {
        g_.nextNodes_[from].push_back(to);
    }
    
    Graph<NodeType> build() {
        return std::move(g_);
    }
    
    friend class Graph<NodeType>;
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

template<class NodeType>
struct UndirGraphBuilder : DirGraphBuilder<NodeType> {
    
    using DirGraphBuilder<NodeType>::g_;
    
    virtual void add(NodeType from, NodeType to) {
        g_.nextNodes_[from].push_back(to);
        g_.nextNodes_[to].push_back(from);
    }
    
    friend class Graph<NodeType>;
};


struct UndirGraphUtil {
    
    template<class Graph, class Handler>
    static void forEachEdge(const Graph& g, Handler handler) {
        for (auto i = 0; i < g.nodeCount(); ++i) {
            for (auto j : g.nextNode(i)) {
                if (i < j) {
                    handler(i, j);
                }
            }
        }
    }
    
    template<class EdgedGraph, class Handler>
    static void forEachIndexedEdge(const EdgedGraph& g, Handler handler) {
        for (auto i = 0; i < g.nodeCount(); ++i) {
            for (auto p : g.nextPairs(i)) {
                if (i < p.node) {
                    handler(i, p.node, p.edge);
                }
            }
        }
    }
    
};


struct DirGraphUtil {
    
    template<class Graph, class Handler>
    static void forEachEdge(const Graph& g, Handler handler) {
        for (auto i = 0; i < g.nodeCount(); ++i) {
            for (auto j : g.nextNode(i)) {
                handler(i, j);
            }
        }
    }
    
    template<class EdgedGraph, class Handler>
    static void forEachIndexedEdge(const EdgedGraph& g, Handler handler) {
        for (auto i = 0; i < g.nodeCount(); ++i) {
            for (auto p : g.nextPairs(i)) {
                handler(i, p.node, p.edge);
            }
        }
    }
    
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
    : graph(graph), edgeValues(edgeValues) {
        
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
        return std::tuple<std::vector<Value>, std::vector<bool>>{res, visited};
    }
    
private:
    const EdgedGraph& graph;
    const std::vector<Value>& edgeValues;
};





int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto test = 0; test < T; ++test) {
        int N, M, K, S, L;
        cin >> N >> M >> K >> S >> L;
        --S; --L;
        DirEdgedGraphBuilder<int, int> builder(N);
        vector<int> len(M);
        for (auto m = 0; m < M; ++m) {
            int di, ci, li;
            cin >> di >> ci >> li;
            --di; --ci;
            builder.add(di, ci);
            len[m] = li;
        }
        
        auto g = builder.build();
        auto gR = g.reversed();
        
        DijkstraShortestPath<decltype(g), int> d(g, len);
        DijkstraShortestPath<decltype(g), int> dR(gR, len);
        
        vector<int> distS;
        vector<bool> visS;
        tie(distS, visS) = d.Compute(S);
        
        vector<int> distL;
        vector<bool> visL;
        tie(distL, visL) = dR.Compute(L);
        
        auto min_path = numeric_limits<int>::max(); 
        
        // check regular path if exists
        if (visS[L]) {
            min_path = min(min_path, distS[L]);
        }
        
        for (auto k = 0; k < K; ++k) {
            int uj, vj, qj;
            cin >> uj >> vj >> qj;
            --uj; --vj;
            if (visS[uj] && visL[vj]) {
                min_path = min(min_path, distS[uj] + distL[vj] + qj);
            }
            if (visL[uj] && visS[vj]) {
                min_path = min(min_path, distL[uj] + distS[vj] + qj);
            }
        }
        
        if (min_path == numeric_limits<int>::max()) {
            min_path = -1;
        }
        
        printf("%d\n", min_path);
    }
}


