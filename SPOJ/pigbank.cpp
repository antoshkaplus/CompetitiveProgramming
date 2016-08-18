
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

struct C {
    int p, w;
};

int kInfinity = numeric_limits<int>::max();

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    int E, F;
    cin >> E >> F;
    int N;
    cin >> N;
    vector<C> cs(N);
    for (auto& c : cs) {
        cin >> c.p >> c.w;
    }
    
    int M = F - E;
    // one element for each gram
    vector<int> ps(M, kInfinity);
    // init
    for (auto& c : cs) {
        if (ps.size() <= c.w) continue; 
        ps[c.w-1] = c.p; 
    }
    
    for (int i = 0; i < M; ++i) {
        for (auto& c : cs) {
            if (i - c.w < 0 || ps[i - c.w] == kInfinity) continue;
            ps[i] = min(ps[i-c.w] + c.p, ps[i]);
        }
    }
    if (ps.back() == kInfinity) {
        cout << "This is impossible." << endl; 
    } else {
        cout << "he minimum amount of money in the piggy-bank is " 
            << ps.back() << "." << endl;
    }
}








