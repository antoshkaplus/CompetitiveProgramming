
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


vector<int> ReadVector(int N) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}


int main() {

    int T; 
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N_1, N_2;
        cin >> N_1;
        auto v_1 = ReadVector(N_1);
        cin >> N_2;
        auto v_2 = ReadVector(N_2);
        
        auto res = numeric_limits<int>::max();
        sort(v_1.begin(), v_1.end());
        for (auto v : v_2) {
            // something greater or equal
            auto it = lower_bound(v_1.begin(), v_1.end(), v);
            if (it != v_1.end()) {
                res = min(res, abs(*it - v));
            }
            if (it != v_1.begin()) {
                res = min(res, abs(*(it-1) - v));
            }
        }
        cout << res << endl;
    }
}
