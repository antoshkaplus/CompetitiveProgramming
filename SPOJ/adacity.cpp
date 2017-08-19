#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

using Index = int;
using Count = int;
using Int = int;

template<class T>
struct Grid {
    using value_type = T;
    
    typename std::vector<T>::const_iterator begin() const {
        return grid_.begin();
    }
    typename std::vector<T>::iterator begin() {
        return grid_.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return grid_.end();
    }
    typename std::vector<T>::iterator end() {
        return grid_.end();
    }
    
    Grid() : Grid(0, 0) {}
    Grid(Count row_count, Count col_count)
    :   row_count_(row_count), 
    col_count_(col_count), 
    grid_(row_count*col_count) {}
    
    
    void resize(Count row_count, Count col_count) {
        row_count_ = row_count;
        col_count_ = col_count;
        grid_.resize(row_count*col_count);
    }
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
    
    Count cell_count() const { return row_count()*col_count(); } 
    
    T& operator()(Int row, Int col) {
        return grid_[row*col_count_ + col];
    }
    
    const T& operator()(Int row, Int col) const {
        return grid_[row*col_count_ + col];
    }
    
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
};



// finds shortest distances between all pairs of nodes in O(N^3) time
template<class Value>
class FloydWarshall {
    
    Grid<Value> dist_;
    Value max_;
    
    int node_count() const {
        return dist_.row_count();
    }    
    
    const static Value LIMIT;
    
public:
    
    FloydWarshall(int node_count) 
    : dist_(node_count, node_count), max_(0) {
        
        dist_.fill(LIMIT);
    }
    
    
    void AddDirectedDist(int from, int to, Value val) {
        dist_(from, to) = val;
        max_ += val;
    }
    
    void Compute() {
        max_ += 1;
        for (auto& d : dist_) {
            if (d == LIMIT) d = max_;
        }
        auto V = node_count();
        for (auto i = 0; i < V; ++i) {
            dist_(i, i) = 0;
        }
        /* 
         Add all vertices one by one to the set of intermediate vertices.
         ---> Before start of a iteration, we have shortest distances between all
         pairs of vertices such that the shortest distances consider only the
         vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
         ----> After the end of a iteration, vertex no. k is added to the set of
         intermediate vertices and the set becomes {0, 1, 2, .. k} 
         */
        for (auto k = 0; k < V; k++) {
            // Pick all vertices as source one by one
            for (auto i = 0; i < V; i++) {
                // Pick all vertices as destination for the
                // above picked source
                for (auto j = 0; j < V; j++) {
                    // If vertex k is on the shortest path from
                    // i to j, then update the value of dist[i][j]
                    if (dist_(i, k) + dist_(k, j) < dist_(i, j)) {
                        dist_(i, j) = dist_(i, k) + dist_(k, j);
                    }
                }
            }
        }
    }
    
    bool Exists(int from, int to) const {
        return dist_(from, to) != max_;
    }
    
    Value Dist(int from, int to) const {
        return dist_(from, to);
    }
    
}; 

template <class Value>
const Value FloydWarshall<Value>::LIMIT = std::numeric_limits<Value>::max();




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
    
private:
    std::vector<std::vector<NodeType>> nextNodes_;
    
public:
    const std::vector<NodeType>& nextNodes(NodeType n) const {
        return nextNodes_[n];
    }
    
    Count nodeCount() const {
        return nextNodes_.size();
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



enum class BFS_Flow {
    // don't expand on children
    Skip,
    Continue,
    Terminate
};

// we try to Skip before visiting the node, because 
// in current version of algorithm we are about of visiting edges.
// by skipping we cancel addition of outgoing edges from second endpoint   
template<class Process, class EdgedGraph>
void BFS_PrevEdged(const EdgedGraph& gr, Index v, Process& pr) {
    std::queue<Index> q;
    Count c = gr.nodeCount();
    std::vector<bool> visited(c, false);
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (auto p : gr.nextPairs(v)) {
            auto w = p.node;
            if (!visited[w]) {
                BFS_Flow flow = pr(w, v, p.edge);
                if (flow == BFS_Flow::Terminate) return;
                if (flow == BFS_Flow::Skip) continue;
                visited[w] = true;
                q.push(w);
            }
        }
    }
}



// but BFS should be slow right???
template<class DirEdgedGraph, class Value> 
class FordFulkerson {
    
    
    using NodeType = typename DirEdgedGraph::NodeType;
    using EdgeType = typename DirEdgedGraph::EdgeType;
    
    
    struct Edge {
        NodeType from;
        NodeType to;
        
        // i have to copy as I'm going to manipulate it
        Value flow;
        Value capacity;
        
        Edge() {}
        
        Edge(NodeType from, NodeType to, Value flow, Value capacity) 
        : from(from), to(to), flow(flow), capacity(capacity) {}
        
        // if graph is directed then this comparison part is not really needed
        Value ResidualCapacityTo(Index vertex) {
            if      (vertex == from) return flow;            // backward edge
            else if (vertex == to) return capacity - flow;   // forward edge
            else throw std::runtime_error("Illegal endpoint");
        }
        
        void AddResidualFlowTo(Index vertex, Value delta) {
            if      (vertex == from) flow -= delta;           // backward edge
            else if (vertex == to) flow += delta;             // forward edge
            else throw std::runtime_error("Illegal endpoint");
        }
        
    };
    
    std::vector<Edge> edges_;
    EdgedGraph<NodeType, EdgeType> graph_;
    
    
    struct P {
        Index from;
        Index edge;
    };
    
public:
    
    FordFulkerson(const DirEdgedGraph& graph, const std::vector<Value>& edgeValues) : graph_(graph) {
        auto sz = graph.nodeCount();
        
        edges_.resize(graph.edgeCount());
        for (auto i = 0; i < sz; ++i) {
            for (auto a : graph.nextPairs(i)) {        
                edges_[a.edge] = Edge{i, a.node, 0, edgeValues[a.edge]};
            }
        }
        
        UndirEdgedGraphBuilder<NodeType, EdgeType> builder(sz);
        for (auto& e : edges_) {
            builder.add(e.from, e.to);
        }
        graph_ = builder.build();
    }
    
    Value Compute(Index s, Index t) {
        
        auto sz = graph_.nodeCount();
        
        std::vector<P> parent(sz); 
        parent[s].from = s;
        bool t_visited;
        
        auto pr = [&](Index v, Index from, Index edge) {
            if (edges_[edge].ResidualCapacityTo(v) > 0) {
                parent[v] = {from, edge};
                if (v == t) {
                    t_visited = true;   
                    return BFS_Flow::Terminate;
                } 
            } else {
                return BFS_Flow::Skip;
            }
            return BFS_Flow::Continue;
        };
        
        int max_flow = 0;
        
        for (;;) {
            t_visited = false;
            BFS_PrevEdged(graph_, s, pr);
            if (!t_visited) {
                break;
            }
            auto path_flow = std::numeric_limits<Value>::max();
            for (auto v = t; v != s; v = parent[v].from) {
                auto& e = edges_[parent[v].edge];
                path_flow = std::min(path_flow, e.ResidualCapacityTo(v));
            }
            
            for (auto v = t; v != s; v = parent[v].from) {
                edges_[parent[v].edge].AddResidualFlowTo(v, path_flow);
            }
            
            max_flow += path_flow;
        }
        
        return max_flow;
    }
    
    std::vector<Value> flow() const {
        std::vector<Value> res(edges_.size());
        auto getValue = [&](const Edge& e) { return e.flow; };
        std::transform(edges_.begin(), edges_.end(), res.begin(), getValue);
        return res;
    }
    
private:
    
    
};


class MaxBipartiteMatching {
    
    DirEdgedGraphBuilder<Index, Index> builder_;
    Index fromStart_;
    Index toStart_;
    Index src_;
    Index dst_;
    // capacities
    std::vector<Count> edgeValues_;
    
    struct M {
        Index from, to;
        Count count;
        
        M() {}
        M(Index from, Index to, Count count)
        : from(from), to(to), count(count) {}
    };
    
    Count fromSize() const {
        return toStart_ - fromStart_;
    }
    
public:
    
    MaxBipartiteMatching(std::vector<Count> from, std::vector<Count> to) : builder_(0) {
        fromStart_ = 0;
        toStart_ = from.size();
        src_ = toStart_ + to.size();
        dst_ = src_ + 1;
        builder_ = DirEdgedGraphBuilder<Index, Index>(from.size() + to.size() + 2);
        
        for (auto i = 0; i < from.size(); ++i) {
            builder_.add(src_, fromStart_+i);
            edgeValues_.push_back(from[i]);
        }
        for (auto i = 0; i < to.size(); ++i) {
            builder_.add(toStart_+i, dst_);
            edgeValues_.push_back(to[i]);
        }
    }
    
    void addDirEdge(Index from, Index to, Count val) {
        builder_.add(fromStart_+from, toStart_+to);
        edgeValues_.push_back(val);
    }
    
    // maybe do it different way
    std::vector<M> Compute() {
        auto g = builder_.build();
        FordFulkerson<decltype(g), Count> ff(g, edgeValues_);
        ff.Compute(src_, dst_);
        edgeValues_ = ff.flow();
        return matching(g);
    }
    
    std::vector<M> matching(const EdgedGraph<Index, Index>& g) {
        std::vector<M> r;
        for (auto i = 0; i < fromSize(); ++i) {
            auto from = i + fromStart_;
            for (auto p : g.nextPairs(from)) {
                if (edgeValues_[p.edge] > 0) {
                    r.emplace_back(i, p.node-toStart_, edgeValues_[p.edge]);
                }
            }
        }
        return r;
    }
};



int main() {
    ifstream cin("../in.txt");
    int test_count;
    cin >> test_count;
    for (auto test = 0; test < test_count; ++test) {
        int N, M, F, T;
        cin >> N >> M >> F >> T;
        // N cities, F friends
        vector<Count> from(N, 0);
        vector<Count> to(N, 1);
        for (auto i = 0; i < F; ++i) {
            int city;
            cin >> city; --city;
            ++from[city]; 
        }
        
        MaxBipartiteMatching bm(from, to);

        // M roads
        FloydWarshall<int> fw(N);
        for (auto i = 0; i < M; ++i) {
            int A, B, L;
            cin >> A >> B >> L; --A; --B;
            if (fw.Dist(A, B) < L) continue;
            
            fw.AddDirectedDist(A, B, L);
			fw.AddDirectedDist(B, A, L);
        }
        fw.Compute();
        //cout << fw.Dist(1, 3) << endl;
        for (auto from_i = 0; from_i < N; ++from_i) {
            for (auto to_i = 0; to_i < N; ++to_i) {
                if (!fw.Exists(from_i, to_i) || fw.Dist(from_i, to_i) > T) continue;
                bm.addDirEdge(from_i, to_i, from[from_i]);
                //cout << from_i << " " << to_i << " " << from[from_i] << endl;
            }
        }
		
		auto matching = bm.Compute();
		set<int> s;
		for (auto& m : matching) {
			s.insert(m.to);
		}
		cout << s.size() << endl;
    }

}
