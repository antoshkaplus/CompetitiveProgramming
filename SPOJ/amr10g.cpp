
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


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N, K;
        cin >> N >> K;
        vector<uint64_t> hs(N);
        for (auto& h : hs) {
            cin >> h;
        }
        sort(hs.begin(), hs.end());
        uint64_t mm = numeric_limits<uint64_t>::max();
        for (auto i = 0; i < hs.size()-K+1; ++i) {
            auto pp = hs[i+K-1] - hs[i];
            if (pp < mm) mm = pp;
        }
        cout << mm << endl;
    }
    
}