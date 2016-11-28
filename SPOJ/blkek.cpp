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


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int N;
    cin >> N;
    for (int n = 0; n < N; ++n) {
        string s;
        cin >> s;
        
        vector<int> ps;
        int es = 0;
        for (auto ch : s) {
            if (ch == 'K') {
                ps.push_back(es);
            } else if (ch == 'E') {
                ++es;
            }
        }
        vector<int> ps_sum(ps.size()); 
        if (!ps.empty()) ps_sum[0] = ps[0];
        for (int i = 1; i < ps.size(); ++i) {
            ps_sum[i] = ps_sum[i-1] + ps[i];
        }
        
        // after reduction
        uint64_t res = 0;
        for (auto i = 0; i < ps.size(); ++i) {
            res += ps_sum.back() - ps_sum[i] - (ps.size() - i - 1) * ps[i];
        }
        
        cout << res << endl;
    }
    
}

