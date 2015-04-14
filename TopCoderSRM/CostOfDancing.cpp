#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct CostOfDancing {
    int minimum(int k, vector<int> cost) {
        sort(cost.begin(), cost.end());
        int s = 0;
        for (int i = 0; i < k; ++i) {
            s += cost[i];
        }
        return s;
    }
};