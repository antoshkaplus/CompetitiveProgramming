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
#include <cstring>
#include <fstream>

using namespace std;

using Count = int;
using Index = int;
using Int = int;

using Direction = int;

constexpr Direction kDirUp = 0;
constexpr Direction kDirDown = 1;
constexpr Direction kDirRight = 2;
constexpr Direction kDirLeft = 3;    


// make it possible to substruct
struct Indent {
    constexpr Indent() : Indent(0, 0) {}
    constexpr Indent(Int row, Int col) : row(row), col(col) {}
    
    void set(Int row, Int col) {
        this->row = row;
        this->col = col;
    }
    
    Int area() const {
        return row*col;
    }
    
    Int row, col;
};

struct Position {
    // operators see below
    constexpr Position() : Position(0, 0) {}
    constexpr Position(Int row, Int col) : row(row), col(col) {}
    
    //Position(Int row, Int col) : row(row), col(col) {}
    
    void set(Int row, Int col) {
        this->row = row;
        this->col = col;
    }
    
    void shift(Int row, Int col) {
        this->row += row;
        this->col += col;
    }
    
    Position& operator+=(const Indent& indent) {
        row += indent.row;
        col += indent.col;
        return *this;
    }
    
    Position& operator=(const Position& p) {
        row = p.row;
        col = p.col;
        return *this;
    }
    
    void swap() {
        std::swap(row, col);
    }
    Position swapped() const {
        return Position(col, row);
    }
    
    Position shifted(Int row_shift, Int col_shift) const {
        return {row + row_shift, col + col_shift};
    }
    
    
    Int row, col;
    
    struct TopLeftComparator {
        bool operator()(const Position& p_0, const Position& p_1) {
            return p_0.row < p_1.row || (p_0.row == p_1.row && p_0.col < p_1.col);
        }
    };
    struct BottomRightComparator {
        bool operator()(const Position& p_0, const Position& p_1) {
            return p_0.row > p_1.row || (p_0.row == p_1.row && p_0.col > p_1.col);
        }
    };
};   


Position operator+(const Position& p, const Indent& n) {
    return {p.row + n.row, p.col + n.col};
}        


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
    
    T& operator[](const Position& p) {
        return grid_[p.row*col_count_ + p.col];
    }
    const T& operator[](const Position& p) const {
        return grid_[p.row*col_count_ + p.col];
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
    
    
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
};




template<class Key>
class IndexMap {
public:
    
    IndexMap() : newIndex_(0) {}
    
    bool exists(const Key& key) const {
        return m_.count(key) != 0;
    }
    
    Index index(const Key& key) {
        auto p = m_.emplace(key, newIndex_);
        if (p.second) {
            ++newIndex_;
        }
        return p.first->second;
    }
    
    Index index(const Key& key) const {
        return m_.at(key);
    }
    
    auto begin() {
        return m_.begin();
    }
    
    auto end() {
        return m_.end();
    }
    
    int size() const {
        return m_.size();
    }
    
private:
    Index newIndex_;
    std::map<Key, Index> m_;
};



namespace HopcroftKarp
{
    const int MAX = 10000;
    
    int N, M;
    std::vector<int> adj[MAX];
    int left[MAX], right[MAX];
    int dist[MAX];
    bool used[MAX];
    
    void initialize(int n, int m)
    {
    N = n, M = m;
    
    std::fill(left, left + MAX, -1);
    std::fill(right, right + MAX, -1);
    std::fill(used, used + MAX, false);
    
    for (int i = 0; i < N; ++i) adj[i].clear();
    }
    
    void add_edge(int u, int v)
    {
    adj[u].push_back(v);
    }
    
    void bfs()
    {
    std::queue<int> q;
    
    for (int i = 0; i < N; ++i)
        {
        if (!used[i]) dist[i] = 0, q.push(i);
        else dist[i] = 1 << 30;
        }
    
    while (!q.empty())
        {
        int u = q.front();
        q.pop();
        
        for (int const v : adj[u])
            {
            if (right[v] != -1 && dist[right[v]] == 1 << 30)
                {
                dist[right[v]] = dist[u] + 1;
                q.push(right[v]);
                }
            }
        }
    }
    
    bool dfs(int u)
    {
    for (int const v : adj[u])
        {
        if (right[v] == -1 || (dist[right[v]] == dist[u] + 1 && dfs(right[v])))
            {
            used[u] = true;
            left[u] = v, right[v] = u;
            
            return true;
            }
        }
    
    return false;
    }
    
    int matching()
    {
    for (int answer = 0;;)
        {
        bfs();
        
        int flow = 0;
        for (int i = 0; i < N; ++i)
            {
            if (!used[i] && dfs(i)) ++flow;
            }
        
        if (!flow) return answer;
        answer += flow;
        }
    }
}


int main() {
    int T;
    cin >> T;
    auto read = [&](int& r) {
        cin >> r; --r;
    };
    for (auto t = 0; t < T; ++t) {
        int N;
        cin >> N;
        Grid<int> g(N, N);
        g.ForEach(read);
        
        auto toIndex = [=](const Position& p) {
            return p.row*N + p.col;
        };
        auto toPos = [=](const Index i) {
            return Position(i/N,i%N);
        };
        
        IndexMap<int> ms[10];
        
        auto func = [&] (const Position& p) {
            ms[g[p]].index(toIndex(p));
        };
        g.ForEachPosition(func);
        
        int k;
        Index idx;
        auto handle = [&](const Grid<int>& g, int dir, const Position& pos) {
            if (g[pos] == k+1) {
                HopcroftKarp::add_edge(idx, ms[k+1].index(toIndex(pos)));
            }
        };
        
        bool yes = true;
        for (k = 0; k < 9; ++k) {
            HopcroftKarp::initialize(ms[k].size(), ms[k+1].size());
            for (auto p : ms[k]) {
                idx = p.second;
                g.ForEachNearby(toPos(p.first), handle);
            }
            auto m = HopcroftKarp::matching();
            if (m != ms[k+1].size()) {
                yes = false;
                break;
            }
        }
        cout << (yes ? "YES" : "NO") << endl; 
    }
}
