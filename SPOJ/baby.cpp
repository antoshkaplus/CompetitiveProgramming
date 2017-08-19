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
 
const int N_MAX = 16; 

using BS = bitset<N_MAX>; 
 
 
struct S { 
 
    using CV = const vector<int>;
 
    array<int, 1 << N_MAX> t;
    // queen positions
    // contains columns for each row
    CV& before;
    CV& after;
 
    int N;
    
    S(CV& before, CV& after) : before(before), after(after) {
        N = before.size();
    }
 
    // placing i-th queen
    // return minimum amount of moves to place what is left including i-th queen
    int solve(int i, BS& left) {
        if (i == N) return 0;
    
        if (t[left.to_ulong()] != -1) {
            return t[left.to_ulong()];
        }
        
        int r = numeric_limits<int>::max();
        for (auto j = 0; j < N; ++j) {
            if (!left[j]) {
                left.reset(j);
                r = min(r, abs(i-j) + abs(before[i]-after[j]) + solve(i+1, left));
                left.set(j);
            }
        }
        return t[left.to_ulong()] = r;
    }

};


vector<int> ReadVector(int N) {
    // be careful while reading
    // 1 based indexes
    vector<int> r(N);
    for (auto& rr : r) {
        cin >> rr;
        --rr;
    }
    return r;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    for (;;) {
        cin >> N;
        if (N == 0) {
            break;
        }
        auto before = ReadVector(N);
        auto after = ReadVector(N);
        cout << S.solve(before, after) << endl;
    }
}