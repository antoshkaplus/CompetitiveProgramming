#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

using AdjacencyList = std::vector<std::vector<int>>;


bool DFS(const AdjacencyList& adj_list, int n, int not_used) {
    int V = adj_list.size();
    std::vector<bool> vis(V, false);
    int vis_count = 0;
    std::stack<int> st;
    st.push(n);
    while (!st.empty() && vis_count != V - not_used) {
        int t = st.top();
        st.pop();
        if (!vis[t]) {
            vis[t] = true;
            ++vis_count;
            for (int a : adj_list[t]) {
                if (!vis[a]) st.push(a);
            }
        }
    } 
    return vis_count == V - not_used;
}

AdjacencyList Reverse(const AdjacencyList& adj) {
    int V = adj.size();
    AdjacencyList adj_new(V);
    for (int i = 0; i < V; ++i) {
        for (int j : adj[i]) {
            adj_new[j].push_back(i);
        }
    }
    return adj_new;
}


// for directed graph

// can implement is connected similar way

// would need to reverse
bool HasEulerianCycle(const AdjacencyList adj_list, int not_used) {
    int V = adj_list.size();
    // our starting vertex
    int n;
    for (int i = 0; i < V; ++i) {
        if (adj_list[i].size() > 0) {
            n = i;
            break;
        }
    }
    bool vis = DFS(adj_list, n, not_used);
    if (!vis) return false;
    
    auto adj_list_2 = Reverse(adj_list);
    for (int i = 0; i < V; ++i) {
        if (adj_list_2[i].size() != adj_list[i].size()) {
            return false;
        }
    }
    
    vis = DFS(adj_list_2, n, not_used);
    return vis;
}







int main() {
    constexpr int N = ('z'-'a') + 1;
    
    int T;
    cin >> T;
    array<int, N> A;
    for (int t = 0; t < T; ++t) {
        AdjacencyList adj(N);
        vector<bool> vis(N, false);
        fill(A.begin(), A.end(), 0);
        int M;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            string word;
            cin >> word;
            int s = word.front()-'a';
            int e = word.back()-'a';
            ++A[s];
            --A[e];
            vis[s] = vis[e] = true;
            adj[s].push_back(e);
        }   
        int not_used = 0;
        for (int i = 0; i < N; ++i) {
            bool b = vis[i];
            if (!b) ++not_used;
        }
        
        int s = -1;
        int e = -1; 
        bool possible = true;
        for (int i = 0; i < N; ++i) {
            if (A[i] > 0) {
                if (s >= 0 || A[i] > 1) {
                    possible = false;
                    break;
                } 
                s = i;
            }
            if (A[i] < 0) {
                if (e >= 0 || A[i] < -1) {
                    possible = false;
                    break;
                }
                e = i; 
            }
        }
        if (possible) {
            adj[e].push_back(s);
            possible = HasEulerianCycle(adj, not_used);
        }
        cout << (possible ? "Ordering is possible." : "The door cannot be opened.") << endl;
    }
}


/*
 // test case
 
 9 
 2 
 abcd 
 dcba 
 1 
 aa 
 3 
 aaa 
 bbb 
 ccc 
 4 
 masti 
 ishq 
 bc 
 cb 
 3 
 bc 
 cb 
 aa 
 2 
 aaa 
 bbb 
 4 
 ab 
 bc 
 ca 
 dd 
 3 
 ab 
 bc 
 ca 
 6 
 ab 
 bc 
 ca 
 zf 
 fg 
 gz

*/
