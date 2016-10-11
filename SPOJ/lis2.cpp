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

// We actually have to use segment tree

struct P {
    int x, y;
    
    bool operator<(const P& p) const {
        return x < p.x && y < p.y;
    }
   	
   	bool operator>(const P& p) const {
        return p < *this;
   	}
    
    bool operator==(const P& p) const {
        return x == p.x && y == p.y;
    }
};

constexpr P P_EMPTY{numeric_limits<int>::min(), numeric_limits<int>::min()}; 

// it seems we have to keep more than we want for this problem

// Binary search (note boundaries in the caller)
template<class T>
int CeilIndex(std::vector<T> &v, int l, int r, T key) {
    while (r-l > 1) {
        int m = l + (r-l)/2;
        if (!(v[m] < key)) // middle is equivalent to key or greater
            r = m;
        else
            l = m;
    }
    
    return r;
}

template<class T>
int LongestIncreasingSubsequenceLength(std::vector<T> &v) {
    if (v.empty()) return 0;
    
    std::vector<vector<T>> tail(v.size(), P_EMPTY);
    int length = 1; // always points empty slot in tail
    
    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        // should be less than all??
        if (v[i] < tail[0])
            // new smallest value
            tail[0] = v[i];
        else if (v[i] > tail[length-1])
            // v[i] extends largest subsequence
            tail[length++] = v[i];
        else
            // v[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than v[i]
            // (and also, v[i] would have already appeared in one of LIS, identify the location and replace it)
            
            // this guy has to be rewritten
            int index = CeilIndex(tail, -1, length-1, v[i]);
            
            tail[] = v[i];
    }
    
    return length;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N; 
    cin >> N;
    vector<P> ps(N);
    for (auto& p : ps) {
        cin >> p.x >> p.y;
    }
    cout << LongestIncreasingSubsequenceLength(ps);
}
