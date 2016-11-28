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
#include <fstream>

using namespace std;

using Index = int;
using Count = int;
using Int = int;

template<class Key>
class IndexMap {
public:
    
    IndexMap() : newIndex_(0) {}
    
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
    
    
    auto begin() const {
        return m_.begin();
    }
    
    auto end() const {
        return m_.end();
    }
    
    
    int size() const {
        return m_.size();
    }
    
private:
    Index newIndex_;
    std::map<Key, Index> m_;
};


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
    
    // function takes in element
    template<class Process>
    void ForEach(Process& proc) {
        for (Index r = 0; r < row_count(); ++r) {
            for (Index c = 0; c < col_count(); ++c) {
                proc((*this)(r, c));
            }
        }
    }
    
    
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
    
    friend struct const_iterator;
    template<class U>
    friend bool operator==(const Grid<U>& g_0, const Grid<U>& g_1);
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
    : dist_(node_count, node_count, LIMIT), max_(0) {}
    
    
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


using Delivery = std::bitset<12>;  

struct Order {
    int i_1, i_2; 
    int count;
    // start index
    int bit_index;
    // count of bits that represent left overs
    int bit_count;
};

int get(Order& d, Delivery& del) {
    int c = 0;
    for (auto i = d.bit_count-1; i >= 0; --i) {
        c <<= 1;
        c |= del[d.bit_index + i];
    }
    return c;
}

void put(const Order& d, Delivery& del, int t) {
    Delivery b(t);
    for (auto i = 0; i < d.bit_count; ++i) {
        del[d.bit_index + i] = b[i]; 
    }
}

Delivery Produce(vector<Order>& orders) {
    
    auto bitsNeeded = [](int t) {
        return int(ceil(log2(t)));
    };
    
    int start = 0;
    
    auto fillBits = [&](Order& r) {
        r.bit_index = start;
        // + zero value
        r.bit_count = bitsNeeded(r.count+1);
        start += r.bit_count;
    };
    
    for_each(orders.begin(), orders.end(), fillBits);
    
    Delivery del;
    for (auto& r : orders) {
        put(r, del, r.count);
    }
    return del;
}



struct Solver {
    
    Solver(vector<Order>& orders, const Grid<int>& dist, int home) 
    : orders_(orders), dist_(dist), home_(home) {
        
        fill_n((int*)t, 11 * (1 << 11), -1);
    }
    
    
    int solve() {
        auto del = Produce(orders_);
        return solve(home_, del);
    }
    
private:
    
    
    // returns shortest distance to travel
    // city is current city
    int solve(int city, const Delivery& del) {
        if (del.none()) {
            return dist_(city, home_);
        }
        
        auto& cell = t[city][del.to_ulong()];
        if (cell != -1) {
            return cell; 
        }
        
        const static int MAX_DIST = numeric_limits<int>::max();
        int min_dist = MAX_DIST;
        for (auto& d : orders_) {
            
            auto del_new = del;
            //cout << del_new << endl;
            auto c = get(d, del_new);
            if (c == 0) continue;
            
            --c;
            put(d, del_new, c);
            //cout << del_new << endl;
            auto y = solve(d.i_2, del_new) + dist_(d.i_1, d.i_2) + dist_(city, d.i_1);
            if (y < min_dist) {
                min_dist = y;
            }
        }
        
        return cell = min_dist;
    }
    
private:
    vector<Order>& orders_;
    const Grid<int> dist_;
    int home_;
    int t[11][1 << 11];
};


// return grid with distances
Grid<int> Reduce(const FloydWarshall<int>& fw, const IndexMap<int>& m) {
    auto sz = m.size();
    Grid<int> r(sz, sz);
    for (auto p_1 : m) {
        for (auto p_2 : m) {
            r(p_1.second, p_2.second) = fw.Dist(p_1.first, p_2.first);
        }
    }
    return r;
}



int main(int argc, char **argv) {
    //ifstream cin("../in.txt");
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, M, B;
        cin >> N >> M >> B;
        --B;
        FloydWarshall<int> paths(N);
        for (auto i = 0; i < M; ++i) {
            int i_1, i_2, d;
            cin >> i_1 >> i_2 >> d;
            --i_1;
            --i_2;
            if (d < paths.Dist(i_1, i_2)) {
                paths.AddDirectedDist(i_1, i_2, d);
                paths.AddDirectedDist(i_2, i_1, d);
            }
        }
        paths.Compute();
        int order_count;
        cin >> order_count;
        vector<Order> orders(order_count);
        // so we map old stuff to new stuff
        // 5 orders => 10 cities
        IndexMap<int> m;
        for (auto& d : orders) {
            cin >> d.i_1 >> d.i_2 >> d.count;
            --d.i_1;
            --d.i_2;
            d.i_1 = m.index(d.i_1);
            d.i_2 = m.index(d.i_2);
            
        }
        auto home = m.index(B);
        auto ds = Reduce(paths, m);
        
        Solver s(orders, ds, home);
        cout << s.solve() << endl;
    }
    
}