
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
#include <deque>
#include <assert.h>

using namespace std;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<vector<int>> counts;
    vector<int> importance;
    vector<int> parent;
    for (auto t = 0; t < T; ++t) {
        int N;
        cin >> N;
        adj.resize(N);
        for (auto& a : adj) {
            a.clear();
        }
        
        int u, v;
        for (auto i = 0; i < N-1; ++i) {
            cin >> u >> v;
            --u;
            --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        } 
        visited.resize(N);
        fill(visited.begin(), visited.end(), false);
        counts.resize(N);
        for (auto& c : counts) {
            c.clear();
        }
        importance.resize(N);
        fill(importance.begin(), importance.end(), 0);
        parent.resize(N);
        
        queue<int> q;
        q.push(0);
        visited[0] = true; 
        parent[0] = 0;
        stack<int> st;
        st.push(0);
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            for (auto i : adj[t]) {
                if (i == parent[t]) continue;
                q.push(i);
                st.push(i);
                parent[i] = t;
            }
        }
        while (!st.empty()) {
            auto t = st.top();
            st.pop();
            auto& cs = counts[t]; 
            for (auto i = 0; i < cs.size(); ++i) {
                for (auto j = i+1; j < cs.size(); ++j) {
                    importance[t] += cs[i]*cs[j];
                }
            }
            // changing places between agents
            importance[t] *= 2;
            int s = accumulate(cs.begin(), cs.end(), 0);
            importance[t] += 2*s + 1;
            counts[parent[t]].push_back(s+1);
        }
        int S = 0;
        for (auto i = 0; i < N; ++i) {
            S += ((i+1)*(unsigned long long)importance[i])%1000000007;
            S %= 1000000007;
        }
        cout << S << endl;
    }
    
    
}













