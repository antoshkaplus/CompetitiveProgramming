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
#include <fstream>
#include <array>
#include <iomanip>


using namespace std;


struct P {
    int x, y; 
};


double dist(const P& p_1, const P& p_2) {
    return sqrt(pow((double)p_1.x - p_2.x, 2) + pow(double(p_1.y - p_2.y), 2));
}

struct S {
    
    const vector<P>& ps;
    vector<vector<double>> tbl;
    
    
    S(const vector<P>& ps) : ps(ps) {
        int sz = ps.size();
        tbl.resize(ps.size(), vector<double>(ps.size(), -1));
        // have to make round
        for (auto i = 0; i < sz-1; ++i) {
            // with next move would get to sz-1 = end
            tbl[i][sz-2] = tbl[sz-2][i] = dist(ps[i],ps[sz-1]) + dist(ps[sz-2],ps[sz-1]);
        }
        // solution for size = 1;
        for (auto i = 0; i < sz; ++i) {
            tbl[i][sz-1] = tbl[sz-1][i] = 0;
        }
    }
    
    // we return best two path distance where all on the right are placed 
    double solve(int i_1, int i_2) {
        if (tbl[i_1][i_2] != -1) {
            return tbl[i_1][i_2];
        }
        // if one is finished we have to finish another one
        int i_3 = max(i_1, i_2)+1;
        return tbl[i_1][i_2] = tbl[i_2][i_1] = min(dist(ps[i_1], ps[i_3]) + solve(i_3, i_2),
                                                   dist(ps[i_2], ps[i_3]) + solve(i_1, i_3));
    }
};



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    // if one point print result immediatly
    int N;
    cin >> N;
    vector<P> ps(N);
    for (auto& p : ps) {
        cin >> p.x >> p.y;
    }
    
    S s(ps);
    cout << fixed << setprecision(2) << s.solve(0, 0) << endl;
} 

