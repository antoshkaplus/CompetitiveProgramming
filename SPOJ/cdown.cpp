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

vector<vector<int>> Reverse(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<vector<int>> adj_new(V);
    for (int i = 0; i < V; ++i) {
        for (int j : adj[i]) {
            adj_new[j].push_back(i);
        }
    }
    return adj_new;
}


template<class Key, class Value>
std::map<Value, Key> FlipMap(const std::map<Key, Value>& m) {
    std::map<Value, Key> flip_m;
    for (auto& p : m) {
        flip_m[p.second] = p.first;
    }
    return flip_m;
}


const int SOL_SIZE = 3; 


class S {
public:
    struct Sol {
        int id;
        int count;
        
        bool operator<(const Sol& s) const {
            return count > s.count;
        }
        
    };
    
    struct A {
        
        A(int gen) : counts(gen, 0) {}
        
        // how many of each generation
        vector<int> counts;
        // best solution so far
        vector<Sol> sol;
        
        void merge(const A& a) {
            mergeSol(sol, a.sol);
            mergeCounts(counts, a.counts);
        }
        
        static void mergeSol(vector<Sol>& res, const vector<Sol>& m) {
            int res_n = res.size();
            res.insert(res.end(), m.begin(), m.end());
            inplace_merge(res.begin(), res.begin()+res_n, res.end());
            
            if (res.size() <= SOL_SIZE) return;
            
            int index = SOL_SIZE;
            while (index < res.size() && res[index].count == res[index-1].count) ++index;
            res.resize(index);
        }  
        
        // first element is number of children of this dude
        static void mergeCounts(vector<int>& res, const vector<int>& m) {
            for (auto i = 0; i < res.size(); ++i) {
                res[i] += m[i];
            }
        }
        
    };
    
    const vector<vector<int>>& children;
    int gen;
    
    S(const vector<vector<int>>& children, int gen) : children(children), gen(gen) {}
    
    // returns result
    A solve(int i) {
        A r(gen);
        for (int ch : children[i]) {
            auto a = solve(ch);
            r.merge(a);
        }
        // is current guy worthy?
        r.counts.insert(r.counts.begin(), children[i].size());
        r.counts.pop_back();
        if (r.counts.back() > 0) {
            A::mergeSol(r.sol, vector<Sol>{Sol{i, r.counts.back()}});
        }
        return r;
    }
    
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n, d;
        cin >> n >> d;
        vector<vector<int>> chs;
        int new_id = 0;
        map<string, int> name_to_id;
        auto get_id = [&](const string& name) {
            auto p = name_to_id.emplace(name, new_id);
            if (p.second) {
                ++new_id;
                chs.resize(new_id);
            }
            return p.first->second;
        };
        
        string name;
        for (auto i = 0; i < n; ++i) {
            cin >> name;
            auto id = get_id(name);
            
            int c;
            cin >> c;
            for (auto j = 0; j < c; ++j) {
                cin >> name;
                chs[id].push_back(get_id(name));
            }
        }
        auto id_to_name = FlipMap(name_to_id);
        
        auto chs_rev = Reverse(chs);
        int root = -1;
        for (auto i = 0; i < chs_rev.size(); ++i) {
            if (chs_rev[i].size() == 0) {
                root = i;
            }
        }
        if (root == -1) throw runtime_error("lol");
        S s(chs, d);
        auto a = s.solve(root);
        
        sort(a.sol.begin(), a.sol.end(), [&](const S::Sol& s_1, const S::Sol& s_2) {
            return s_1.count > s_2.count || 
            (s_1.count == s_2.count && id_to_name[s_1.id] < id_to_name[s_2.id]);
        });
        
        
        cout << "Tree " << t+1 << endl;
        for (auto s : a.sol) {
            cout << id_to_name[s.id] << " " << s.count << endl;
        }
    }
}

