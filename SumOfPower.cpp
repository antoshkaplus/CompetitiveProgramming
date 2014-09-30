#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct SumOfPower {
    int findSum(vector<int> v) {
        int s = 0;
        for (int i = 0; i < v.size(); ++i) {
            s += v[i]*((i+1)*(v.size()-i));
        }
        return s;
    }
};