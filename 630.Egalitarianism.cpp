

#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

class Egalitarianism3Easy {
public:
int maxCities(int n, vector<int> a, vector<int> b, vector<int> len) {
    vector<vector<int>> adjLen(n);
    vector<vector<int>> adjNode(n);
    for (int i = 0; i < n-1; ++i) {
        adjNode[a[i]].push_back(b[i]);
        adjLen[a[i]].push_back(len[i]);
        adjNode[b[i]].push_back(a[i]);
        adjLen[b[i]].push_back(len[i]);
    }
    
    
    
    
    
    
    
    if (n <= 2) return n; 
    int dist[10][10];
    fill_n(*dist, 100, 1000000);
    for (int i = 0; i < n-1; ++i) {
        dist[b[i]-1][a[i]-1] = dist[a[i]-1][b[i]-1] = len[i];
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            for (int i_0 = 0; i_0 < n; ++i_0) {
                for (int i_1 = i_0+1; i_1 < n; ++i_1) {
                    if (dist[i_0][i_1] > dist[i_0][i] + dist[i][i_1]) {
                        dist[i_0][i_1] = dist[i_0][i] + dist[i][i_1];
                        dist[i_1][i_0] = dist[i_0][i] + dist[i][i_1];
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    
    int maxK = 2;
    for (int i = 0; i < n; ++i) {
        map<int, int> m;
        for (int j = 0; j < n; ++j) {
            if (i == j || dist[i][j] > 10000) continue;
            if (m.find(dist[i][j]) != m.end()) {
                ++m[dist[i][j]];
            } else {
                m[dist[i][j]] = 1;
            }
        }
        for (auto p : m) {
            if (p.second > maxK) {
                maxK = p.second;
            }
        }
    }
    return maxK;
}
};