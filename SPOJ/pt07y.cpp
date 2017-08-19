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
#include <array>
#include <fstream> 
#include <memory>


using namespace std;

using Count = int;
using Index = int;

template<class T>
using AdjacencyList = std::vector<std::vector<T>>;

using NodeAdjacencyList = AdjacencyList<Index>;



// struct provides access on reading. 
// const prevents alternating variables 
// immutable class
// like wrapper
// can't use unique_ptr here or will be unable to copy
template <class NodeAdjacencyListPtr>
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
    
    
    // and now we have to do a bunch of definitions... it sucks pretty bad
    
    
};

Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<const NodeAdjacencyList>& ptr);
Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<NodeAdjacencyList>& ptr);

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList* ptr);
Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList& ptr);



Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<const NodeAdjacencyList>& ptr) {
    return Graph<std::shared_ptr<const NodeAdjacencyList>>(ptr);
}

Graph<std::shared_ptr<const NodeAdjacencyList>> CreateGraph(const std::shared_ptr<NodeAdjacencyList>& ptr) {
    return Graph<std::shared_ptr<const NodeAdjacencyList>>(std::const_pointer_cast<const NodeAdjacencyList>(ptr)); 
}

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList* ptr) {
    return Graph<const NodeAdjacencyList*>(ptr);
}

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList& ptr) {
    return CreateGraph(&ptr);
}


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
    int N, M;
    cin >> N >> M;
    if (M != N-1) {
        cout << "NO";
        return 0;
    }
    NodeAdjacencyList adj_list(N);
    for (int i = 0; i < N-1; ++i) {
        int v, w;
        cin >> v >> w;
        --v; --w;
        adj_list[v].push_back(w);
        adj_list[w].push_back(v);
    }
    vector<bool> arr(N, false);
    auto func = [&](auto v) {
        arr[v] = true;
        return false;
    };
    BFS(CreateGraph(adj_list), 0, func);
    cout << (find(arr.begin(), arr.end(), false) == arr.end() ? "YES" : "NO");
    
} 