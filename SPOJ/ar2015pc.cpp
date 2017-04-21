
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


template <class T, class S, class C>
void clearpq(priority_queue<T, S, C>& q) {
    struct HackedQueue : private priority_queue<T, S, C> {
        static S& Container(priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
    HackedQueue::Container(q).clear();
}


template<class EdgedGraph, class Value>
class DijkstraShortestPath {
    
    struct Item {
        Index orig;
        Index dst;
        Value val;
        
        Item(Index orig, Index dst, Value val) 
        : orig(orig), dst(dst), val(val) {}
        
        bool operator<(const Item& t) const {
            // need min priority queue
            return val > t.val;
        }
        
    };
    
    struct R2 {
        Index orig;
        Value val;
        
        R2() {}
        
        R2(Index orig, Value val) 
        : orig(orig), val(val) {}
    };
    
    
public:
    DijkstraShortestPath(const EdgedGraph& graph, const std::vector<Value>& edgeValues) 
    : graph(graph), edgeValues(edgeValues), rs(graph.nodeCount()) {
        
    }
    
    
    std::tuple<Value, bool> Compute(Index src, Index dst) {
        if (src == dst) return make_tuple(0, true);
        
        clearpq(q);
        std::fill(rs.begin(), rs.end(), R2(-1, 0));
        
        q.emplace(src, src, 0);
        q.emplace(dst, dst, 0);
        
        for (;;) {
            if (q.empty()) cout << "lol" <<endl;
            auto t = q.top();
            q.pop();
            if (rs[t.dst].orig == t.orig) continue;
            if (rs[t.dst].orig != -1) {
                return make_tuple(rs[t.dst].val + t.val, true);
            }
            rs[t.dst] = {t.orig, t.val};
            
            for (auto p : graph.nextPairs(t.dst)) {
                if (rs[p.node].orig != t.orig) {
                    q.emplace(t.orig, p.node, t.val + edgeValues[p.edge]);
                }
            }
        }
        return make_tuple(0, false);
    }
    
    
private:
    const EdgedGraph& graph;
    const std::vector<Value>& edgeValues;
    
    std::vector<R2> rs; 
    std::priority_queue<Item> q;
    
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
            tie(val, vis) = pp.Compute(S, D);
            cout << val << endl;
        }
    }
    
}
