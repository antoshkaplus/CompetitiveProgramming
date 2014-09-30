#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct ManySquares {
    int howManySquares(vector<int> sticks) {
        sort(sticks.begin(), sticks.end());
        int n = 0;
        for (int i = 0; i < sticks.size();) {
            if (sticks[i] == sticks[i+3]) {
                ++n; 
                i+=4;
            } else {
                ++i;
            }
        }
        return n;
    }
};
