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




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int H, W;
        cin >> H >> W;
        vector<vector<int>> vs;
        for (auto& v : vs) {
            v = ReadVector(W);
        }
        vector<int> res(W);
        reverse(vs.begin(), vs.end());
        for (auto h = 0; h < H; ++h) {
            auto& rs = vs[h]; 
            for (int i = 0; i < W; ++i) {
                int s = rs[i];
                if (i != 0) {
                    s = max(s, rs[i-1]);
                }
                if (i != W-1) {
                    s = max(s, rs[i+1]);
                }
                res[i] += s;
            }
        }
        cout << *max_element(res.begin(), res.end()) << endl;
    }
}

