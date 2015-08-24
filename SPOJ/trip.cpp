
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

using namespace std;



struct Problem {
    
    struct R {
        int no_s_1_sz;
        int no_s_2_sz;
    }
    
    // need to initialize with -1
    R t[1000][1000];
    
    string s_1;
    string s_2;
        
    
    // return max sz
    int solve(int i_1, int i_2) {
        if (i_1 == -1 || i_2 == -1) return 0; 
        if (s_1[i_1] == s_2[i_2]) {
            // should put this value in our table somehow
            return solve(i_1-1, i_2-1) + 1;
        }
        R& r = t[i_1][i_2];
        if (r.no_s_1_sz == -1) r.no_s_1_sz = solve(i_1-1, i_2);
        if (r.no_s_2_sz == -1) r.no_s_2_sz = solve(i_1, i_2-1);
        return max(r.no_s_1_sz, r.no_s_2_sz);
    }
    
    vector<string> gather(int i_1, int i_2) {
        if (i_1 == -1 || i_2 == -1) return {""}; 
        
        if (s_1[i_1] == s_2[i_2]) {
            auto ss = gather(i_1-1, i_2-1);
            for (auto& s : ss) {
                s += s_1[i_1];
            } 
            return ss;
        }
        R r = t[i_1][i_2];
        if (r.no_s_1_sz > r.no_s_2_sz) {
            return gather(i_1-1, i_2);
        }
        if (r.no_s_1_sz < r.no_s_2_sz) {
            return gather(i_1, i_2-1);
        }
        auto v_1 = gather(i_1-1, i_2);
        v_1.insert(v_2.begin(), v_2.end());
        sort(v_1.begin(), v_1.end());
        v_1.erase(unique(v_1.begin(), v_1.end()), v_1.end());
        return v_1;
    }
    
    vector<string> solve(string s_1, string s_2) {
        this->s_1 = s_1;
        this->s_2 = s_2;
        for (int i_1 = 0; i_1 < s_1.size(); ++i_1) {
            for (int i_2 = 0; i_2 < s_2.size(); ++i_2) {
                t[i_1][i_2].no_s_1_sz = -1;
                t[i_1][i_2].no_s_2_sz = -1;
            }
        }
        // this one initializes everything
        int sz = solve(s_1.size()-1, s_2.size()-1);
        cout << "all sizes: " << sz << endl;
        return gather(s_1.size()-1, s_2.size()-1);
        
    }

};





int max;
vector<string> ss;


void find(const string& s_0, int i_0, const string& s_1, int i_1, string& res) {
    if (i_0 == s_0.size() || i_1 == s_1.size()) {
        if (max > res.size()) return;
        if (max < res.size()) {
            ss.clear();
            max = res.size();
        }
        ss.push_back(res);
        return;
    }
    
    if (s_0[i_0] != s_1[i_1]) {
        // take in i_0
        auto t_1 = std::find(s_1.begin() + i_1, s_1.end(), s_0[i_0]);
        if (t_1 != s_1.end()) {
            res += s_0[i_0];
            find(s_0, i_0+1, s_1, t_1-s_1.begin()+1, res);
            res.pop_back();
        } 
        
        // take in i_1
        auto t_0 = std::find(s_0.begin() + i_0, s_0.end(), s_1[i_1]);
        if (t_0 != s_0.end()) {
            res += s_1[i_1];
            find(s_0, t_0-s_0.begin()+1, s_1, i_1+1, res);
            res.pop_back();
        }
        
        // take in nothing
        find(s_0, i_0 + 1, s_1, i_1 + 1, res);
    } else {
        res += s_0[i_0];
        find(s_0, i_0 + 1, s_1, i_1 + 1, res);
        res.pop_back();
    }
}

void find(string s_0, string s_1) {
    string res;
    find(s_0, 0, s_1, 0, res);
}



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    Problem p;
    string t_0, t_1;
    for (int t = 0; t < T; ++t) {
        cin >> t_0 >> t_1;
        auto ss = p.solve(t_0, t_1);
        for (auto& s : ss) {
            cout << s << endl;
        }
    } 
}











