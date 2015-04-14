#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;


#define ST  stack
#define ST_i ST<int>
#define ST_i64 ST<int64_t>

#define V  vector
#define V_i V<int>
#define V_s V<string>
#define V_b V<bool>
#define V_V_i V<V_i>

#define P_ii pair<int, int>
#define P   pair

#define M_ii map<int, int>
#define M   map

#define S_i set<int>
#define S set

#define ODD(n) ((n)%2 != 0) 
#define EVEN(n) ((n)%2 == 0)

#define ACCUMULATE()


struct Jumping {
    string ableToGet(int x, int y, V_i jumpLength) {
        // need to get x and y after jumping around
        // 
        int sum = accumulate()
        
        
    }
};


// 1
struct Target {
    V_s draw(int n) {
        V_s res(n);
        for (int i = 0; i < n; ++i) res[i].resize(n, ' ');
        
        for (int sz = n, ind = 0; sz > 0; sz-=4, ind+=2) {
            for (int i = 0; i < sz; ++i) {
                res[ind][ind + i] = res[ind + sz - 1][ind + i] = 
                res[ind + i][ind] = res[ind + i][ind + sz - 1] = '#';
            }
        }
        return res;
    }
};
