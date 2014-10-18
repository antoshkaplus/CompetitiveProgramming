#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;


#define ST  stack
#define ST_i ST<int>
#define ST_i64 ST<int64_t>

#define V_i vector<int>
#define V_V_i vector<V_i>
#define V  vector

#define P_ii pair<int, int>
#define P   pair

#define M_ii map<int, int>
#define M   map

#define S_i set<int>
#define S set


// 3
struct LonglongestPathTree {
    
    V_V_i adjaceny_list_;
    V_V_i weights_;
    
    
    struct Item {
        Item(int node, int parent, long long distance) 
        : node(node), parent(parent), distance(distance) {}
        int node;
        int parent;
        long long distance;
    };

    struct Result {
        int node;
        long long distance;
    };
    
    long long FindLongestDistance(int root, int banned_node) {
        long long max_d = -1;
                
        ST<Item> st;
        st.emplace(root, -1, 0);
        while (!st.empty()) {
            Item item = st.top();
            st.pop();
            auto& adj = adjaceny_list_[item.node];
            // if (adj.size() == 1) {
            // unusable because of high degree of banned node
            if (item.distance > max_d) {
                max_d = item.distance;
            }
            auto& ws = weights_[item.node]; 
            //cout << item.node << " " << item.parent << " " << item.distance << endl;
            for (int i = 0; i < adj.size(); ++i) {
                if (adj[i] == item.parent || adj[i] == banned_node) continue;
                st.emplace(adj[i], item.node, item.distance + ws[i]);
            }
        }
        return max_d;
    }
    
    int FindFarthestNode(int root, int parent) {
        long long max_d = -1;
        int max_i = -1;
        
        ST<Item> st;
        st.emplace(root, parent, 0);
        while (!st.empty()) {
            Item item = st.top();
            st.pop();
            auto& adj = adjaceny_list_[item.node];
            if (adj.size() == 1) {
                if (item.distance > max_d) {
                    max_d = item.distance;
                    max_i = item.node;
                }
            }
            auto& ws = weights_[item.node]; 
            for (int i = 0; i < adj.size(); ++i) {
                if (adj[i] == item.parent) continue;
                st.emplace(adj[i], item.node, item.distance + ws[i]);
            }
        }
        return max_i;
    }
    
    long long getLength(V_i a, V_i b, V_i len) {
        adjaceny_list_.resize(len.size() + 1);
        weights_.resize(len.size() + 1);
        for (int i = 0; i < len.size(); ++i) {
            adjaceny_list_[a[i]].push_back(b[i]);
            adjaceny_list_[b[i]].push_back(a[i]);
            weights_[a[i]].push_back(len[i]);
            weights_[b[i]].push_back(len[i]);
        }
        long long max_d = -1;
        for (int i = 0; i < len.size(); ++i) {
            //cout << i << endl;
            int n_0 = FindFarthestNode(a[i], b[i]);
            long long d_0 = FindLongestDistance(n_0, b[i]);
            //cout << n_0 << " " << d_0 << endl;
            int n_1 = FindFarthestNode(b[i], a[i]);
            long long d_1 = FindLongestDistance(n_1, a[i]);
            //cout << n_1 << " " << d_1 << endl;
            
            
            long long d = d_0 + d_1 + len[i];
            if (d > max_d) {
                max_d = d;
            }
        }
        return max_d;
    }
};



// 2 should use some sort of selection algorithm
class QuadraticLaw {
public:
    long long getTime(long long d) {
        return (-1 + (long long)sqrt(double(4*d + 1)))/2;
    }
};

// 1
class IdentifyingWood {
public:
    string check(string s, string t) {
        int j = 0;
        string result = "Nope."; 
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == t[j]) ++j;
            if (j == t.size()) {
                result = "Yep, it's wood.";
                break;
            }
        }
        return result;
    }
};





