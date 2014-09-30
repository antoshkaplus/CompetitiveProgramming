#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <limits>


using namespace std;

struct NegativeGraphDiv2 {
    
    struct E {
        int v;
        int w;
    };
    
    struct I {
        int v;
        long long d;
        bool operator<(const I& i) const {
            return d > i.d;
        }
    };
    
    void distance_to_point(
        int i, bool is_first,
        const vector<bool>& reachable, 
        vector<long long>& ds, 
        vector<vector<E>>& adj) {
        
        priority_queue<I> pr_q;
        vector<bool> visited(ds.size(), false);
        pr_q.push({i, ds[i]});
        while (!pr_q.empty()) {
            
            auto p = pr_q.top();
            pr_q.pop();
            if (visited[p.v]) {
                continue;
            }
           
            // distance already assigned
            visited[p.v] = true;
            ds[p.v] = p.d;
            //if (is_first && p.v == ds.size()-1) continue;
             
            for (auto e : adj[p.v]) {
                //if (!is_first && e.v == ds.size()-1) continue;
                if (reachable[e.v] && !visited[e.v] && p.d + e.w < ds[e.v]) {
                    ds[e.v] = p.d + e.w;
                    pr_q.push({e.v, ds[e.v]});
                }
            }
        }
    }
    
    void update(const vector<long long>& source, vector<long long>& target) {
        for (int i = 0; i < source.size(); ++i) {
            if (source[i] < target[i]) {
                target[i] = source[i];
            }
        }
    }
    
    long long findMin(
        int N, 
        vector<int> s, 
        vector<int> t, 
        vector<int> w, 
        int charges) {
        
        for (int i = 0; i < s.size(); ++i) {
            --s[i];
            --t[i];
        }
        
        // init this 
        vector<vector<E>> first_adj(N);
        vector<vector<E>> last_adj(N);
        
        for (int i = 0; i < s.size(); ++i) {
            first_adj[s[i]].push_back({t[i], w[i]});
            last_adj[t[i]].push_back({s[i], w[i]});
        }
    
        auto limit = numeric_limits<long long>::max();
        
        // charges, vertex => distance
        vector<vector<long long>> dist_to_first(
            charges+1, 
            vector<long long>(N, limit));
        vector<vector<long long>> dist_to_last(
            charges+1, 
            vector<long long>(N, limit));
        
        dist_to_first[0][0] = 0;
        dist_to_last[0][N-1] = 0;
        
        distance_to_point(0, 1, vector<bool>(N, true), dist_to_first[0], first_adj);
        distance_to_point(N-1, 0, vector<bool>(N, true), dist_to_last[0], last_adj); 
        
        vector<bool> reachable(N, true);
        for (int i = 0; i < N; ++i) {
            if (dist_to_first[0][i] == limit || dist_to_last[0][i] == limit) {
                reachable[i] = false;
            }
        }

        
        for (int i = 0; i < N; ++i) {
            cout << dist_to_first[0][i] << ", " << dist_to_last[0][i] << endl;
        }
        cout << endl;
        
        // now we have all distances needed
        for (int i = 1; i <= charges; ++i) {
            dist_to_first[i] = dist_to_first[i-1];
            dist_to_last[i] = dist_to_last[i-1];
            for (int j = 0; j < s.size(); ++j) {
                if (!reachable[s[j]] || !reachable[t[j]]) {
                    continue;
                }
                vector<long long> dist = dist_to_first[i-1];
                if (dist_to_first[i-1][s[j]] - w[j] < dist_to_first[i][t[j]]) {
                    dist[t[j]] = dist_to_first[i-1][s[j]] - w[j];                
                    distance_to_point(t[j], 1, reachable, dist, first_adj);
                    update(dist, dist_to_first[i]);
                } 
                dist = dist_to_last[i-1];
                if (dist_to_last[i-1][t[j]] - w[j] < dist_to_last[i][s[j]]) {
                    dist[s[j]] = dist_to_last[i-1][t[j]] - w[j];                
                    distance_to_point(s[j], 0, reachable, dist, last_adj);
                    update(dist, dist_to_last[i]);
                } 
            }
            for (int j = 0; j < N; ++j) {
                cout << dist_to_first[i][j] << ", " << dist_to_last[i][j] << endl;
            } 
            cout << endl;
        }
        long long m = numeric_limits<long long>::max();
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k <= charges; ++k) {
                if (reachable[i] && m > dist_to_first[k][i] + dist_to_last[charges-k][i]) {
                    m = dist_to_first[k][i] + dist_to_last[charges-k][i];
                }
            }
        }
        return m;
    }
};