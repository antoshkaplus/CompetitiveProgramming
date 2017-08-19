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

vector<vector<int>> ReadVectorV(int N, int M) {
    vector<vector<int>> res(N);
    for (auto& r : res) {
        r = ReadVector(M);
    }
    return res;
}




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, M, K;
        cin >> N >> M >> K;
        
        auto b_cost = ReadVector(N);
        auto costs = ReadVectorV(N, M);
        auto rates = ReadVectorV(N, M);
        
        vector<int> res(K+1);
        for (auto i = 0; i < N; ++i) {
            auto& cs = costs[i];
            auto& rs = rates[i];  
            vector<int> preres(K+1, 0);
            for (auto j = 0; j < M; ++j) {
                auto c = cs[j];
                auto r = rs[j];
                // we don't need exact price. we can overpay no problem.
                for (auto k = c; k <= K; ++k) {
                    preres[k] = max(preres[k], preres[k-c] + r);
                }
            }
            auto b = b_cost[i];
            rotate(preres.rbegin(), preres.rbegin()+b, preres.rend());
            fill_n(preres.begin(), b, 0);
            
            for (auto k = 1; k <= K; ++k) {
                auto r = 0;
                for (auto k_2 = 0; k_2 <= k; ++k_2) {
                    r = max(r, res[k_2] + preres[k-k_2]);
                }
                res[k] = r;
            }
        }
        cout << res.back() << endl;
        
    }
    
    
    
}