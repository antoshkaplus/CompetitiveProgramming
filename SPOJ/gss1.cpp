// uses RangeMinInterval
// data structure can be generalized

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
class RangeMI {
    
    
    struct I {
        T dr;
        T dl;
        T whole;
        T dd;
    };
    
    struct RI {
        T dr;
        T dd;
    };
    
    struct LI {
        T dl;
        T dd;
    };
    
    static LI left_I(const I& t) {
        return {t.dl, t.dd};
    }
    
    static RI right_I(const I& t) {
        return {t.dr, t.dd};
    }
    
    static I to_I(const T& t) {
        return I{t, t, t, t};
    }
    
    static I merge(const I& left, const I& right) {
        I res;
        res.whole = left.whole + right.whole;
        res.dl = min(right.dl, left.dl + right.whole); 
        res.dr = min(left.dr, right.dr + left.whole);
        res.dd = min(right.dd, min(left.dd, right.dr + left.dl));
        return res;
    }
    
public:
    
    RangeMI(const std::vector<T>& vs) {
        leaf_int_ = vs.size();
        perfect_leaf_int_ = perfect_leafs(leaf_int_);
        int nodes_c = perfect_nodes(perfect_leaf_int_) - perfect_leaf_int_ + leaf_int_;
        Is_.resize(nodes_c);
        std::vector<bool> inited(nodes_c, false);
        for (int i = 0; i < leaf_int_; ++i) {
            Is_[i + nodes_c - leaf_int_] = to_I(vs[i]);
            inited[i + nodes_c - leaf_int_] = true;
        }    
        for (int i = nodes_c-1; i > 0; --i) {
            int p = (i-1)/2;
            if (!inited[p]) {
                Is_[p] = Is_[i];
                inited[p] = true;
            } else { 
                Is_[p] = merge(Is_[i], Is_[p]); 
            }
        }
    }

    T MI(int i, int n) {
        return MI(0, i, n, 0, leaf_int_, perfect_leaf_int_);
    }
    
private:
    
    int perfect_leafs(int leaf_int) {
        int p = std::ceil(log2(leaf_int));
        return std::pow(2, p);
    }
    
    int perfect_nodes(int perf_leaf_int) {
        return 2*perf_leaf_int -1;
    }    

    T MI(int q, int i, int n_i, int m, int n_m, int n_t) {
        if (i == m && n_i == n_m) {
            auto t = n_int(q);
            return t.dd;
        }
        int s = n_t / 2;
        if (i + n_i <= m + s) {
            return MI(l_ch(q), i, n_i, m, std::min(s, n_m), s);
        }
        if (i >= m + s) {
            return MI(r_ch(q), i, n_i, m+s, n_m-s, s);
        }
        LI t = MILeft(l_ch(q), i, m, std::min(s, n_m), s);
        RI t_2 = MIRight(r_ch(q), i+n_i-1, m+s, n_m-s, s);
        
        return min( t.dl+t_2.dr, min(t.dd, t_2.dd));
    }
    
    LI MILeft(int q, int i, int m, int n_m, int n_t) {
        if (i == m) {
            return left_I(n_int(q));
        }
        int s = n_t / 2;
        if (i < m + s) {
            I t = n_int(r_ch(q));
            LI t_left = MILeft(l_ch(q), i, m, std::min(n_m, s), s);
            LI res;
            res.dd = min(t.dr + t_left.dl, min(t.dd, t_left.dd));
            res.dl = min(t.dl, t.whole + t_left.dl);
            return res;
        } 
        return MILeft(r_ch(q), i, m+s, n_m-s, s);
    }
    
    RI MIRight(int q, int i, int m, int n_m, int n_t) {
        if (i == m + n_m - 1) {
            return right_I(n_int(q));
        }
        int s = n_t / 2;
        if (i < m + s) {
            return MIRight(l_ch(q), i, m, std::min(n_m, s), s);
        }
        I t = n_int(l_ch(q));
        RI t_right = MIRight(r_ch(q), i, m+s, n_m - s, s);
        RI res;
        res.dd = min(t.dl + t_right.dr, min(t.dd, t_right.dd));
        res.dr = min(t.dr, t.whole + t_right.dr);
        return res;
    }
    
    int l_ch(int parent) {
        return 2*parent + 1;
    }
    
    int r_ch(int parent) {
        return 2*parent + 2;
    }
    
    const I& n_int(int node) {
        return Is_[node];
    } 
    
    int perfect_leaf_int_;
    int leaf_int_;
    std::vector<I> Is_;
}; 



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> numbs(N);
    for (auto i = 0; i < N; ++i) {
        cin >> numbs[i];
        numbs[i] *= -1;
    }
    RangeMI<int> range(numbs);
    
    int M;
    cin >> M;
    for (auto i = 0; i < M; ++i) {
        int xi, yi;
        cin >> xi >> yi;
        int res = range.MI(xi-1, yi-xi+1);
        cout << -res << endl;
    }
}





