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

using Int = int;
using Count = int;
using Index = int;

using Direction = int;

constexpr Direction kDirUp = 0;
constexpr Direction kDirDown = 1;
constexpr Direction kDirRight = 2;
constexpr Direction kDirLeft = 3; 

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
    
    Position Shifted(Direction dir) const;
    
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


template<class T>
struct Grid {
    using value_type = T;
    
    Grid() : Grid(0, 0) {}
    Grid(Count row_count, Count col_count)
    :   row_count_(row_count), 
    col_count_(col_count), 
    grid_(row_count*col_count) {}
    
    Grid(Count row_count, Count col_count, const T& value_type) 
    :   row_count_(row_count),
    col_count_(col_count),
    grid_(row_count*col_count, value_type) {}
    
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
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
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
            proc(*this, kDirDown, {t.row-1, t.col});
        }
        if (t.row < row_count_-1) {
            proc(*this, kDirUp, {t.row+1, t.col});
        }
        if (t.col > 0) {
            proc(*this, kDirRight, {t.row,t.col-1});
        }
        if (t.col < col_count()-1) {
            proc(*this, kDirLeft, {t.row, t.col+1});
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
    Index index(const Position& p) {
        return p.row*col_count_ + p.col;
    }
    
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
};


vector<int> ReadVector(int N) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}


struct S {
    
    struct P {
        // time to get there
        int t = numeric_limits<int>::max();
        // height
        int h;
        // max up distance travelled // it's not just time divided by 2
        int d = numeric_limits<int>::max();
        
        Position pos;
        
        bool operator<(const P& p) const {
            return d < p.d || (d == p.d && t < p.t);
        }
        
        bool operator>(const P& p) const {
            return p < *this;
        }
        
        P to(const P& p) const {
            bool uphill = p.h > h;
            return {t + abs(p.h-h), p.h, max(d, uphill ? abs(p.h-h) : 0), p.pos};
        }
        
    };
    
    template <class T>  
    using V = vector<T>;
    
    Grid<P> g;
    
    int N;
    
    S(const Grid<int>& g_local, int N) : g(N, N), N(N) {
        auto f = [&](const Position& p) {
            g[p].h = g_local[p];
            g[p].pos = p;
        };
        g.ForEachPosition(f);
        g(0, 0).d = g(0, 0).h;
        g(0, 0).t = g(0, 0).h;
    }
    
    int solve() {
        priority_queue<P, vector<P>, greater<P>> q;
        P p_old = g(0, 0);
        q.push(p_old);
        
        auto f = [&](Grid<P>& g, int dir, const Position& p_new) {
            P c = g[p_old.pos].to(g[p_new]);
            if (c < g[p_new]) {
                g[p_new] = c;
                q.push(c);
            }
        };
        
        while (!q.empty()) {
            p_old = q.top();
            q.pop();
            g.ForEachNearby(p_old.pos, f);
        }
    }
    
    int time() const {
        return g(N-1, N-1).t;
    }
    int dist() const {
        return g(N-1, N-1).d;
    }
    
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, time;
        cin >> N >> time;
        Grid<int> g(N, N);
        auto f = [&](const Position& p) {
            cin >> g[p];
        };
        g.ForEachPosition(f);
        
        S s(g, N);
        s.solve();
        if (s.time() > time) {
            cout << "NO" << endl;
        } else {
            cout << "YES : " << s.dist() << " " << time - s.time() << endl;
        }
    }
}

