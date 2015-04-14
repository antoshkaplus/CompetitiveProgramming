

#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

#define STi stack<int>
#define ST stack
#define Vi vector<int>
#define P pair
#define Pii pair<int, int>
#define Mii map<int, int>
#define Si set<int>


class Egalitarianism3Easy {
public:
    
    map<Pii, int> distMap;
    
    int dist(int i, int j) {
        return distMap[{i, j}];
    }
    
    int maxCities(int n, vector<int> a, vector<int> b, vector<int> len) {
        if (n <= 2) return n;
        
        vector<vector<int>> adjNode(n);
        for (int i = 0; i < n-1; ++i) {
            --a[i];
            --b[i];
            adjNode[a[i]].push_back(b[i]);
            adjNode[b[i]].push_back(a[i]);
            distMap[{a[i], b[i]}] = len[i];
            distMap[{b[i], a[i]}] = len[i];
        }
        
        int maxCount = 2;
        
        for (int i = 0; i < n; ++i) {
            Mii m;
            for (int j : adjNode[i]) {
                Si s;
                // node, parent
                ST<Pii> st;
                Vi d(n, -1);
                d[i] = 0;
                st.emplace(j, i);
                while (!st.empty()) {
                    Pii p = st.top();
                    d[p.first] = dist(p.first, p.second) + d[p.second];
                    s.insert(d[p.first]);
                    st.pop();
                    for (int k : adjNode[p.first]) {
                        if (k == p.second) continue;
                        st.emplace(k, p.first);
                    }
                }
                for (int dd : s) {
                    if (m.count(dd)) {
                        ++m[dd]; 
                    } else m[dd] = 1;
                }
            }
            for (Pii t : m) {
                if (t.second > maxCount) maxCount = t.second;
            }
        }
        
        return maxCount;
    }
    
};