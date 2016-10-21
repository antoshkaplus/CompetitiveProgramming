#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <array>
#include <fstream>
#include <sstream>

using namespace std;

using Index = int;

inline std::vector<std::string> Split(std::string str, char delim) {
    std::vector<std::string> r;
    Index s_i = 0; // starting index for sustr
    for (Index i = 0; i < str.size(); ++i) {
        if (str[i] == delim) {
            r.push_back(str.substr(s_i, i-s_i));
            s_i = i+1;
        }
    }
    r.push_back(str.substr(s_i));
    return r;
}

template <typename Iter>
std::string Join(Iter begin, Iter end, std::string const& separator)
{
    std::ostringstream result;
    if (begin != end) {
        result << *begin++;
    }
    while (begin != end) {
        result << separator << *begin++;
    }
    return result.str();
}

std::string ToLowerCase(const std::string& str) {
    auto res = str;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
} 


struct T {
    string abbr;
    vector<string> ws;
    
    T(const string& abbr, const string& phrase) {
        ws = Split(phrase, ' ');
        this->abbr = ToLowerCase(abbr);
    }
};

void Clean(T& t, set<string>& s) {
    auto& ws = t.ws;
    auto it = remove_if(ws.begin(), ws.end(), [&](const string& ss) {
        return s.count(ss) == 1;
    });
    ws.erase(it, ws.end());
}


struct A {
    
    const static int UNKNOWN = -1;
    const static int MAX = 151; 
    
    int t[MAX][MAX][2];
    
    string p;
    string a;
    
    int solve(const T& tt) {
        p = Join(tt.ws.begin(), tt.ws.end(), " ");
        a = tt.abbr;
        for (auto p_i = 0; p_i <= p.size(); ++p_i) {
            for (auto a_i = 0; a_i <= a.size(); ++a_i) {
                t[p_i][a_i][0] = t[p_i][a_i][1] = UNKNOWN;
            }
        }
        for (auto a_i = 0; a_i < a.size(); ++a_i) {
            t[p.size()][a_i][0] = t[p.size()][a_i][1] = 0;
        }
        t[p.size()][a.size()][1] = 1;
        t[p.size()][a.size()][0] = 0;
        return solve(0, 0, 0);
    }
    
    // i - index in phrase
    // j - index in abbr
    // u - took letter from current word
    // function returns result
    int solve(int i, int j, int u) {
        if (t[i][j][u] != UNKNOWN) {
            return t[i][j][u]; 
        }
        
        int r = 0;
        
        if (p[i] == ' ') {
            if (u) r = solve(i+1, j, 0);
            
        } else {
            
            if (j < a.size() && p[i] == a[j]) {
                r += solve(i+1, j+1, 1);
            }
            
            r += solve(i+1, j, u);
        }
        return t[i][j][u] = r;
    }
};





int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    for (;;) {
        int N;
        cin >> N;
        if (N == 0) break;
        
        set<string> insig_ws;
        for (auto n = 0; n < N; ++n) { 
            string w;
            cin >> w;
            insig_ws.emplace(std::move(w));
        }
        
        for (;;) {
            std::string abbr, phrase;
            cin >> abbr;
            getline(cin, phrase);
            phrase.erase(phrase.begin()); // get rid of first space
            if (abbr == "LAST" && phrase == "CASE") {
                break;
            }
            T t(abbr, phrase);
            Clean(t, insig_ws);
            A a;
            int r = a.solve(t);
            
            cout << abbr << " " << ((r == 0) ? "is not a valid abbreviation" : ("can be formed in " + to_string(r) + " ways")) << endl;
        }
        
        
    }
    
    
    
}

