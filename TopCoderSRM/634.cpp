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

#define UI64 uint64_t
#define UI uint32_t


// 3
struct SpecialStrings {
    
    
    UI64 toNumber(const string& s) {
        UI64 cur = 0; 
        for (int i = 0; i < s.size(); ++i) {
            cur << 1;
            if (s[i] == '1') ++cur;
        }
        return cur;
    }
    
    string toString(UI64 number, int count) {
        return "";
    }
    
    
    string findFeasible(string s) {
        UI64 cur = toNumber(s);
        int n = s.size();
        for (int j = 1; j < n; ++j) {
            if (j < n - j) {
                // first check if already all right
                if ((cur >> (n - j)) <= (cur << (64 - n + j) >> (64 - j))) {
                    continue;
                }
                UI64 p = (cur >> (n - j)) << (n - 2*j);
                cur |= p; 
            } else { // j >= s.size()-j
                if ()
                
                
                for ()
            }
        }
    }

    string findNext(string s) {
        for (int i = s.size()-1; i >= 0; --i) {
            if (s[i] == '0') {
                s[i] = '1';
                string res = findFeasible(s);
                if (res != "") {
                    return res;
                } 
                s[i] = '0';
            } else {
                // make zero because next zero is going to become one
                // like making string ordered
                s[i] = '1';
            }
        }
        return "";
    }
};


// 2
struct ShoppingSurveyDiv2 {
    int minValue(int N, V_i s) {
        V_i c(N, 0);
        int i = 0;
        for (auto ss : s) {
            for (auto j = 0; j < ss; ++j) {
                ++c[(++i)%N]; 
            }
        }
        int count = 0;
        for (int i = 0; i < N; ++i) {
            if (c[i] == s.size()) ++count;
        }
        return count;
    }
};


// 1
struct MountainRanges {
    int countPeaks(V_i hs) {
        int count = 0;
        for (int i = 0; i < hs.size(); ++i) {
            if (i > 0 && hs[i-1] >= hs[i]) continue;
            if (i < hs.size()-1 && hs[i+1] >= hs[i]) continue;
            ++count; 
        }
        return count;
    }
};

