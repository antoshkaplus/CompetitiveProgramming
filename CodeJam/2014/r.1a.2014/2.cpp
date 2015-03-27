//
//  1.cpp
//  
//
//  Created by Anton Logunov on 8/4/14.
//
//

#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <array>

using namespace std;

// returns how many vertices goes with this one
int go(int v, int from_v, const vector<vector<int>>& adj) {
    // one of them is father
    
    // has no children
    if ((adj[v].size() == 1 && from_v != -1) || (adj[v].size() == 0 && from_v == -1)) return 1;
    // has only one child, should be deleted
    // child should be deleted... node is safe
    if ((adj[v].size() == 2 && from_v != -1) || (adj[v].size() == 1 && from_v == -1)) return 1;
    // two or more children
    // which two of them should we take
    array<int, 2> chs = {0, 0};
    // will sort after each...
    for (auto p : adj[v]) {
        if (p == from_v) continue;
        int c = go(p, v, adj);
        if (c > chs[0]) {
            chs[0] = c;
            sort(chs.begin(), chs.end());
        } 
    }
    return 1 + chs[0] + chs[1];
}



int main(int argc, char* argv[]) {
    int T; 
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<vector<int>> adj(N);
        int x, y;
        for (int i = 0; i < N-1; ++i) {
            cin >> x >> y;
            --x;
            --y;
            adj[x].push_back(y);
            adj[y].push_back(x); 
        }
        // which one i root
        int best_root = -1;
        int best_alife = 0;
        for (int root = 0; root < N; ++root) {
            int c = go(root, -1, adj);
        //    cout << c << " ";
            if (c > best_alife) {
                best_root = root;
                best_alife = c;
            }
        }
        cout << "Case #" << t+1 << ": " << N - best_alife << endl;
    }
}













