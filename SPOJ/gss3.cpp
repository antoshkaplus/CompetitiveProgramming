#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
class RangeMI {
    
    struct I {
        T dr;
        T dl;
        T w;
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
    
    static LI L_I(const I& t) {
        return {t.dl, t.dd};
    }
    
    static RI R_I(const I& t) {
        return {t.dr, t.dd};
    }
    
    static I to_I(const T& t) {
        return I{t, t, t, t};
    }
    
    static I merge(const I& L, const I& R) {
        I res;
        res.w = L.w + R.w;
        res.dl = min(R.dl, L.dl + R.w); 
        res.dr = min(L.dr, R.dr + L.w);
        res.dd = min(R.dd, min(L.dd, R.dr + L.dl));
        return res;
    }
    
public:
    
    RangeMI(const std::vector<T>& vs) {
        leaf_int_ = vs.size();
        perf_leaf_int_ = perf_leafs(leaf_int_);
        int nodes_c = perf_nodes(perf_leaf_int_) - perf_leaf_int_ + leaf_int_;
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
        return MI(0, i, n, 0, leaf_int_, perf_leaf_int_);
    }
    
    void Update(int i, T val) {
        U(0, i, perf_leaf_int_, val);
    }
    
private:
    
    void U(int q, int i, int n_t, T val) {
        if (n_t == 1) {
            Is_[q] = to_I(val);
            return;
        } 
        auto s = n_t / 2;
        if (i < s) {
            U(l_ch(q), i, s, val);
        } else {
            U(r_ch(q), i-s, s, val);
        }
        // interval may not be there at all
        if (r_ch(q) < Is_.size()) {
            Is_[q] = merge(n_int(l_ch(q)), n_int(r_ch(q)));
        } else {
            Is_[q] = n_int(l_ch(q));
        }
    }
    
    int perf_leafs(int leaf_int) {
        int p = std::ceil(log2(leaf_int));
        return std::pow(2, p);
    }
    
    int perf_nodes(int perf_leaf_int) {
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
        LI t = MIL(l_ch(q), i, m, std::min(s, n_m), s);
        RI t_2 = MIR(r_ch(q), i+n_i-1, m+s, n_m-s, s);
        
        return min( t.dl+t_2.dr, min(t.dd, t_2.dd));
    }
    
    LI MIL(int q, int i, int m, int n_m, int n_t) {
        if (i == m) {
            return L_I(n_int(q));
        }
        int s = n_t / 2;
        if (i < m + s) {
            I t = n_int(r_ch(q));
            LI t_L = MIL(l_ch(q), i, m, std::min(n_m, s), s);
            LI res;
            res.dd = min(t.dr + t_L.dl, min(t.dd, t_L.dd));
            res.dl = min(t.dl, t.w + t_L.dl);
            return res;
        } 
        return MIL(r_ch(q), i, m+s, n_m-s, s);
    }
    
    RI MIR(int q, int i, int m, int n_m, int n_t) {
        if (i == m + n_m - 1) {
            return R_I(n_int(q));
        }
        int s = n_t / 2;
        if (i < m + s) {
            return MIR(l_ch(q), i, m, std::min(n_m, s), s);
        }
        I t = n_int(l_ch(q));
        RI t_R = MIR(r_ch(q), i, m+s, n_m - s, s);
        RI res;
        res.dd = min(t.dl + t_R.dr, min(t.dd, t_R.dd));
        res.dr = min(t.dr, t.w + t_R.dr);
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
    
    int perf_leaf_int_;
    int leaf_int_;
    std::vector<I> Is_;
}; 


int main() {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> vs(N);
    for (auto& v : vs) {
        cin >> v; v *= -1;
    }
    RangeMI<int> mi(vs);
    int M;
    cin >> M;
    for (auto i = 0; i < M; ++i) {
        int k, x, y;
        cin >> k >> x >> y;
        if (k == 0) {
            mi.Update(x-1, -y);
        } else { // k == 1
            printf("%d\n", -mi.MI(x-1, y-x+1)); 
        }
    }
}
