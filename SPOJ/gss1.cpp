

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

using Count = int;
using Index = int;


// have to test if this is correct data structure
// right now run time error
template<class T>
class RangeMinimum {
public:
    
    // n = 2**(h+1) -1 
    
    // tree consisting only from root node has zero height
    // leaf nodes have zero height
    
    RangeMinimum(const std::vector<T>& vs) : values_(vs) {
        leaf_count_ = vs.size();
        perfect_leaf_count_ = perfect_leafs(leaf_count_);
        Count nodes_c = perfect_nodes(perfect_leaf_count_) - perfect_leaf_count_ + leaf_count_;
        tree_.resize(nodes_c, -1);
        for (Index i = 0; i < leaf_count_; ++i) {
            tree_[i + nodes_c - leaf_count_] = i;
        }   
        // parent i/2     
        for (Index i = nodes_c-1; i > 0; --i) {
            // parent
            Index p = (i-1)/2;
            if (tree_[p] == -1) tree_[p] = tree_[i];
            else if (values_[tree_[p]] > values_[tree_[i]]) {
                tree_[p] = tree_[i];
            }
        }
    }
    
    // could also return corresponding Index
    const T& Minimum(Index i, Count n) {
        return Minimum(0, i, n, 0, leaf_count_, perfect_leaf_count_);
    }
    
private:
    
    Count perfect_leafs(Count leaf_count) {
        // nearest power of 2 for leafs in perfect tree
        Count p = std::ceil(log2(leaf_count));
        return std::pow(2, p);
    }
    
    Count perfect_nodes(Count perf_leaf_count) {
        return 2*perf_leaf_count -1;
    }    
    
    // m = how many elements we have
    // t = how many elements for perfect tree
    
    // children: 2*i, 2*i+1 
    const T& Minimum(Index q, Index i, Count n_i, Index m, Count n_m, Count n_t) {
        //cout << "m: " << q << " " << i << " " << n_i << " " << m << " " << n_m << " " << n_t << endl;
        if (i == m && n_i == n_m) {
            return values_[tree_[q]];
        }
        Count s = n_t / 2;
        // everything on the left
        if (i + n_i < m + s) {
            return Minimum(2*q+1, i, n_i, m, std::min(s, n_m), s);
        }
        // everything on the right
        if (i >= m + s) {
            return Minimum(2*q+2, i, n_i, m+s, n_m-s, s);
        }
        // first left, last right
        const T* t = &MinimumLeft(2*q+1, i, m, std::min(s, n_m), s);
        //cout << "go right? " << n_i << " " <<  s << "\n";
        if (i+n_i > m+s) {
            const T* t_2 = &MinimumRight(2*q+2, i+n_i-1, m+s, n_m-s, s);
            if (*t_2 < *t) t = t_2; 
        }
        return *t;
    }
    
    // left subtree
    const T& MinimumLeft(Index q, Index i, Index m, Count n_m, Count n_t) {
        //cout << "ml: " << q << " " << i << " " << m << " " << n_m << " " << n_t << endl;
        if (i == m) {
            return values_[tree_[q]];
        }
        Count s = n_t / 2;
        if (i < m + s) {
            return std::min(MinimumLeft(2*q+1, i, m, std::min(n_m, s), s),
                            values_[tree_[2*q+1]]);
        } // else
        return MinimumLeft(2*q+2, i, m+s, n_m-s, s);
    }
    
    // right subtree
    const T& MinimumRight(Index q, Index i, Index m, Count n_m, Count n_t) {
        //cout << "mr: " << q << " " << i << " " << m << " " << n_m << " " << n_t << endl;
        if (i == m + n_m - 1) {
            return values_[tree_[q]];
        }
        Count s = n_t / 2;
        if (i < m + s) {
            // not difference actually n_m%s
            return MinimumRight(2*q+1, i, m, n_m-s, s);
        }
        return std::min(values_[tree_[2*q]],
                        MinimumRight(2*q+2, i, m+s, n_m-s, s));
    }
    
    
    // sz - when perfect tree
    // n - now
    Count perfect_leaf_count_;
    Count leaf_count_;
    const std::vector<T>& values_;
    std::vector<Index> tree_; 
    
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
    RangeMinimum<int> range(numbs);
    
    int M;
    cin >> M;
    for (auto i = 0; i < M; ++i) {
        int xi, yi;
        cin >> xi >> yi;
        int res = range.Minimum(xi-1, yi-xi+1);
        cout << -res << endl;
    }
}





