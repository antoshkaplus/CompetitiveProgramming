#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;



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
    
    Grid(Count row_count, Count col_count, const T& value_type) 
    :   row_count_(row_count),
    col_count_(col_count),
    grid_(row_count*col_count, value_type) {}
    
    Grid(const Size& size) : Grid(size.row, size.col) {}
    Grid(std::initializer_list<std::vector<T>> list)
    :   Grid(list.size(), list.size() == 0 ? 0 : list.begin()->size()){
        auto b = list.begin();
        for (auto r = 0; r < row_count(); ++r, ++b) {
            std::copy(b->begin(), b->end(), grid_.begin() + r*col_count());
        }
    }
    
    bool isInside(const Position& p) const {
        return isInside(p.row, p.col);
    }
    bool isInside(Int row, Int col) const {
        return row >= 0 && row < row_count_ && 
        col >= 0 && col < col_count_;
    }
    
    
    bool IsInside(const Position& p) const {
        return isInside(p.row, p.col);
    }
    bool IsInside(Int row, Int col) const {
        return row >= 0 && row < row_count_ && 
        col >= 0 && col < col_count_;
    }
    
    void resize(Count row_count, Count col_count) {
        row_count_ = row_count;
        col_count_ = col_count;
        grid_.resize(row_count*col_count);
    }
    void resize(const Size& size) {
        resize(size.row, size.col);
    }
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
    Size size() const { return Size(row_count(), col_count()); } 
    Count cell_count() const { return row_count()*col_count(); } 
    
    T& operator()(const Position& p) {
        return grid_[p.row*col_count_ + p.col];
    }
    const T& operator()(const Position& p) const {
        return grid_[p.row*col_count_ + p.col];
    }
    
    T& operator[](const Position& p) {
        return grid_[p.row*col_count_ + p.col];
    }
    const T& operator[](const Position& p) const {
        return grid_[p.row*col_count_ + p.col];
    }
    
    T& operator()(Int row, Int col) {
        return grid_[row*col_count_ + col];
    }
    
    const T& operator()(Int row, Int col) const {
        return grid_[row*col_count_ + col];
    }
    
    // function takes in element
    template<class Process>
    void ForEach(Process& proc) {
        for (Index r = 0; r < row_count(); ++r) {
            for (Index c = 0; c < col_count(); ++c) {
                proc((*this)(r, c));
            }
        }
    }
    
    // proc args:
    //      grid itself
    //      from direction
    //      position to process
    template<class Process>
    void ForEachNearby(const Position& t, Process& proc) {
        if (t.row > 0) {
            proc(*this, kDirDown, t+Indent{-1, 0});
        }
        if (t.row < row_count_-1) {
            proc(*this, kDirUp, t+Indent{ 1, 0});
        }
        if (t.col > 0) {
            proc(*this, kDirRight, t+Indent{ 0,-1});
        }
        if (t.col < col_count()-1) {
            proc(*this, kDirLeft, t+Indent{ 0, 1});
        }
    }
    
    // proc arg: const Position&
    template<class Process> 
    void ForEachPosition(Process& proc) const {
        for (Index r = 0; r < row_count(); ++r) {
            for (Index c = 0; c < col_count(); ++c) {
                proc(Position{r, c});
            }
        }
    } 
    
    Grid<T> Transposed() {
        Grid<T> g(col_count(), row_count());
        auto func = [&](const Position& p) {
            g(p.col, p.row) = grid_[index(p)];
        };
        ForEachPosition(func);
        return g;
    }
    
private:
    Index index(const Position& p) {
        return p.row*col_count_ + p.col;
    }
    
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
    
    friend struct const_iterator;
    template<class U>
    friend bool operator==(const Grid<U>& g_0, const Grid<U>& g_1);
};


template<class Process, class AdjacencyListPtr>
void BFS(const Graph<AdjacencyListPtr>& gr, vector<Index> vs, Process& pr) {
    std::queue<Index> q;
    Count c = gr.node_count();
    std::vector<bool> visited(c, false);
    for (auto v : vs) {
        visited[v] = true;
        q.push(v);
    }
    while (!q.empty()) {
        Index v = q.front();
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

template<class Process, class AdjacencyListPtr>
void BFS_Revisit(const Graph<AdjacencyListPtr>& gr, vector<Index> vs, Process& pr) {
    std::queue<Index> q;
    Count c = gr.node_count();
    std::vector<bool> visited(c, false);
    for (auto v : vs) {
        visited[v] = true;
        q.push(v);
    }
    while (!q.empty()) {
        Index v = q.front();
        q.pop();
        // should we also pass from where we came from
        bool b = pr(v);
        if (b) {
            q.push(v);
            continue;
        }
        for (Index w : gr.adjacent(v)) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }

}



using P = array<int, 2>;

struct S {
    int child;
    P parents;
}


class Counter {

    int counter;
    vector<int>& level;

    bool operator()(Index v) {
        // level is always unknown first time
        if (!has_parents(v)) {
            level[v] = 0;
            return false;
        } 
        auto ps = parents(v);
        if (level[ps[0]] == -1 || level[ps[1]] == -1) {
            return true;
        }
        level[v] = 1 + max(level[ps[0]], level[ps[1]]);
        return false;
    }
}



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, K;
        cin >> N >> K;
        // family members numbered from 1 to N
        // K - number of monsters that do have parents
        vector<S> children(K);
        vector<bool> has_parents(N);
        // we can consider it as Adj list
        Grid<int> related(N);
        for (auto& ch : children) {
            cin >> ch.child >> ch.parents[0] >> ch.parents[1];
            --ch.child;
            --ch.parents[0];
            --ch.parents[1];
            has_parents[ch.child] = false;
            
            related(ch.child,ch.parents[0]) = true;
            related(ch.child,ch.parents[1]) = true;
            
        }
        
        for (;;) {
            
        }
        
        
        
        
        vector<int> level(N);
        
        
        vector<int> base_vertices;
        copy_if( range(N) ,  base_vertices, has_no_parents );
        
        // need to build separate data structure
        BFS_Revisit(base_vertices, adj_list, counter );
        
        // so now we got levels;
        
        
        
        
        
        
        
    }    
}