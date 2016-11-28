// look here for beautiful solution to this problem
// https://github.com/cacophonix/SPOJ/blob/master/CLEANRBT.cpp



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
#include <functional>
#include <bitset>

using namespace std;


// this is template because we don't want to use extra memory if there would be
// small number of vertices, but graph is dense, or we need to keep many of them
template<class T>
using AdjacencyList = std::vector<std::vector<T>>;

using NodeAdjacencyList = AdjacencyList<Index>;
using Edge = std::array<Index, 2>;

NodeAdjacencyList EdgesToAdjacencyList(const std::vector<Edge>& edges, size_t node_count);


// struct provides access on reading. 
// const prevents alternating variables 
// immutable class
// like wrapper
// can't use unique_ptr here or will be unable to copy
template <class NodeAdjacencyListPtr, 
EnableIf<IsAnySame<NodeAdjacencyListPtr, std::shared_ptr<const NodeAdjacencyList>, 
const NodeAdjacencyList* >> = enabler >
struct Graph {
    
    NodeAdjacencyListPtr adjacency_list_;
    
    Graph(NodeAdjacencyListPtr adj_list) : adjacency_list_(adj_list) {}  
    
    Count degree(Index i) const {
        return (*adjacency_list_)[i].size();
    }
    
    const std::vector<Index>& adjacent(Index i) const {
        return (*adjacency_list_)[i];
    }
    
    Count node_count() const {
        return adjacency_list_->size();
    }
    
    Count CountEdges() const {
        Count c = 0;
        for (auto i = 0; i < node_count(); ++i) {
            c += adjacent(i).size();
        }
        return c;
    }
    
    // completeness between 0 and 1 : ratio of edges
    static Graph Random(Count node_count, double completeness) {
        std::default_random_engine rng;
        std::uniform_real_distribution<> distr;
        NodeAdjacencyList *adj_list_ptr = new NodeAdjacencyList(node_count);
        NodeAdjacencyList& adj_list = *adj_list_ptr;
        for (auto i = 0; i < node_count; ++i) {
            for (auto j = i+1; j < node_count; ++j) {
                if (distr(rng) < 0.5) continue;
                adj_list[i].push_back(j);
                adj_list[j].push_back(i);
            }
        }        
        return Graph(std::shared_ptr<NodeAdjacencyList>(adj_list_ptr));       
    }
    
    // and now we have to do a bunch of definitions... it sucks pretty bad
    
    
};

// with this bullshit you hide nothing
// everything is exposed.
// there is no OOP programming with this shit
Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<const NodeAdjacencyList>& ptr);
Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<NodeAdjacencyList>& ptr);

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList* ptr);
Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList& ptr);


class GraphBuilder {
    
    int node_count_;
    NodeAdjacencyList adj_list_;
    
    GraphBuilder(int node_count) 
    : node_count_(node_count), adj_list_(node_count) {}
    
    void AddEdge(int i_1, int i_2) {
        adj_list_[i_1].push_back(i_2);
        adj_list_[i_2].push_back(i_1);
    }
    
    Graph<std::shared_ptr<const NodeAdjacencyList>> Build() {
        return Graph<std::shared_ptr<const NodeAdjacencyList>>(std::make_shared<const NodeAdjacencyList>(std::move(adj_list_)));
    }
    
};

// process can return boolean value: if true, then terminate early
template<class Process, class AdjacencyListPtr>
void BFS(const Graph<AdjacencyListPtr>& gr, Index v, Process& pr) {
    std::queue<Index> q;
    Count c = gr.node_count();
    std::vector<bool> visited(c, false);
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        // should we also pass from where we came from
        bool b = pr(v);
        if (b) return;
        for (Index w : gr.adjacent(v)) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    for (;;) {
        int W, H;
        cin >> W >> H;
        if (W == 0 && H == 0) break;
        
        Grid<char> field(H, W);
        for (auto i = 0; i < H; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < W; ++j) {
                field(i, j) = s[j]; 
            }
        }
        Grid<int> g(H+2, W+2, -1);
        int i = 0;
        auto f = [&](const Position& p) {
            switch (field[p]) {
                case '*':
                case 'o':
                case '.':
                    g[p] == i++;
                    break;
                default:
                    break;
            }
        };
        g.ForEachPosition(f);
        GraphBuilder builder(i);
        for (auto i = 1; i <= H; ++i) {
            for (auto j = 1; j <= W; ++j) {
                if (g(i, j) == -1) continue;
                
                if (g(i+1, j) != -1) builder.AddEdge(g(i, j), g(i+1, j));
                if (g(i, j+1) != -1) builder.AddEdge(g(i, j), g(i, j+1));
                if (g(i-1, j) != -1) builder.AddEdge(g(i, j), g(i-1, j));
                if (g(i, j-1) != -1) builder.AddEdge(g(i, j), g(i, j-1));
            }
        }
        // now we look for robo and other guys.
        vector<Index>
        auto pr = [](Index v) {
            
        }
        
        // find robo and other guys and look for distances between them
        
        
        // eventually you get a matrix with all the distances
        // and here you start something called TSP
        
        // that's a lot of coding but we can't make it faster
        
        
        
        // or can be dp approach
    }
    

}