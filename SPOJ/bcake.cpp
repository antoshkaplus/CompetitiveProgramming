// window algorithm
// dynamic programming


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


vector<int> ReadVector(int N) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}


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



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    // somehow need to read test case first
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N, M, K;
        cin >> N >> M >> K;
        Grid<char> g(N, M);
        auto f = [&](const Position& p) {
            cin >> g[p];
        };
        g.ForEachPosition(f);
        
        // we add more values for algo to work
        // bounds won't be used
        Grid<int> win(N+1, M+1, 0);
        for (auto i = N-1; i >= 0; --i) {
            for (auto j = M-1; j >= 0; --j) {
                win(i, j) = (g(i, j) == 'C' ? 1 : 0) + win(i+1, j) + win(i, j+1) - win(i+1, j+1);
            }
        }
        
        auto ans = numeric_limits<int>::max();
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                for (auto i_sz = 1; i_sz <= min(N-i, ans); ++i_sz) {
                    for (auto j_sz = 1; j_sz <= min(M-j, ans/i_sz); ++j_sz) {
                        auto choco = win(i, j) - win(i+i_sz, j) - win(i, j+j_sz) + win(i+i_sz, j+j_sz);
                        if (choco != K) continue;
                        auto area = i_sz*j_sz;
                        if (area < ans) ans = area;
                    }
                }
            }
        }
        if (ans == numeric_limits<int>::max()) ans = -1;
        cout << ans << endl;
    }
}


