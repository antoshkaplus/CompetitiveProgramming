
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
#include <stack>

using namespace std;

struct Pony {
    int s, m, r;
};

struct P_Full {
    P_Full(int t, int i) : t(t), i(i) {}
    int t, i;
    bool operator<(const P_Full& p) const {
        return t > p.t;
    }
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N; // ponies count
    vector<Pony> ps;
    priority_queue<P_Full> full;
    
    for (int i = 0; i < N; ++i) {
        auto& p = ps[i];
        cin >> p.s >> p.m >> p.r;
        int t_full = 0;
        if (p.s == p.m) t_full = 0;
        else if (p.r == 0 && p.m != 0) {
            t_full = numeric_limits<int>::max();
        } else {
        
        }
        full.emplace((p.m - p.s) p.r, )
    }
    
    int M;
    cin >> M; 
    for (int i = 0; i < M; ++i) {
        int t, i_0, i_1; 
        cin >> t >> i_0 >> i_1;
        while ()
    }
    
}













