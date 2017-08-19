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
#include <array>
#include <fstream>


using namespace std;

int N_MAX = 100; // amount of friends // max packets
int K_MAX = 100; // amount of apples in kg
int PRICE_MAX = 1000;

// something else
int TOTAL_MAX = K_MAX*N_MAX*PRICE_MAX+1;


// minimum amount of money to spend
// we consider empty packets cost 0 money
int solve(int N, int K, vector<int> ps) {
    // init dp
    vector<int> dp(K+1);
    dp[0] = 0;
    for (auto i = 1; i <= K; ++i) { 
        dp[i] = TOTAL_MAX;    
    }
    
    for (auto i = 0; i < ps.size(); ++i) {
        // price
        auto p = ps[i];
        if (p == -1) continue;
        
        auto kg = i+1;
        for (auto n = 1; n <= N; ++n) {
            for (auto j = kg; j <= K; ++j) {
                dp[j] = min(dp[j], p + dp[j-kg]);
            }
        }
    }
    
    return dp.back() >= TOTAL_MAX ? -1 : dp.back();
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int C; 
    cin >> C;
    for (auto c = 0; c < C; ++c) {
        int N, K;
        cin >> N >> K;
        vector<int> ps(K);
        for (auto& p : ps) cin >> p;
        
        cout << solve(N, K, ps) << endl;
    }
}





