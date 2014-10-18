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





// 2
struct SortishDiv2 {
    int counter = 0;
    int sortedness;
    
    int compute_sortedness(int i, V_i& seq) {
        int c = 0;
        for (int k = 0; k < seq.size(); ++k) {
            if ((i < k && seq[i] < seq[k]) || (i > k && seq[i] > seq[k])) {
                ++c;
            }
        }
        return c;
    }
    
    void recursion(int from, V_i& seq, int cur_sortedness, V_i& need, V_b& free) {
        if (from == seq.size()) {
            if (cur_sortedness == sortedness) {
                ++counter;
            }
            return;
        }
        for (int i = from; i < seq.size(); ++i) {
            if (seq[i] == 0) {
                for (int k = 0; k < need.size(); ++k) {
                    if (!free[k]) continue;
                    seq[i] = need[k];
                    free[k] = false;
                    int new_sortedness = compute_sortedness(i, seq);
                    recursion(i+1, seq, cur_sortedness + new_sortedness, need, free);
                    free[k] = true;
                }
                seq[i] = 0;
                return;
            }
        }
        recursion(seq.size(), seq, cur_sortedness, need, free);
    }

    int ways(int sortedness, V_i seq) {
        this->sortedness = sortedness;
        int cur_sortedness = 0;
        vector<bool> exist(seq.size(), false);
        for (int s : seq) {
            if (s == 0) continue;
            exist[s-1] = true; 
            for (int s_2 : seq) {
                if (s_2 == 0) continue;
                if (s_2 == s) break;
                if (s > s_2) ++cur_sortedness;
            }
        }
        vector<int> need;
        for (int i = 0; i < seq.size(); ++i) {
            if (!exist[i]) need.push_back(i+1);
        }
        V_b free(need.size(), true);
        recursion(0, seq, cur_sortedness, need, free);
        return counter;
    }
};



// 1
struct GameOfStones {
    int count(V_i stones) {
        bool all_even = all_of(stones.begin(), stones.end(), [](int d) { return d%2 == 0; });
        bool all_odd = all_of(stones.begin(), stones.end(), [](int d) { return d%2 != 0; });
        int sum = accumulate(stones.begin(), stones.end(), 0);
        if (sum % stones.size() != 0) return -1;
        int stones_per_pile = sum / stones.size(); 
        if ((EVEN(stones_per_pile) && all_even) || (ODD(stones_per_pile) && all_odd)) {
            int steps = 0;
            for (int s : stones) {
                if (s < stones_per_pile) {
                    steps += (stones_per_pile - s)/2;
                }
            }
            return steps;
        }
        return -1;
    }
};





















