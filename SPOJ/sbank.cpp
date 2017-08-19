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

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n;
        cin >> n;
        
        map<long long, map<long long, int> > m;
        long long p_0, p_1; 
        long long c, b, a_0, a_1, a_2, a_3;
        const long long mult_0 = 1e+4;
        const long long mult_1 = 1e+8;
        const long long mult_2 = 1e+12;
        
        for (int i = 0; i < n; ++i) {
            cin >> c >> b >> a_0 >> a_1 >> a_2 >> a_3;
            p_0 = c*mult_1 + b;
            p_1 = a_0*mult_2 + a_1*mult_1 + a_2*mult_0 + a_3;
            
            map<long long, int>& mm = m[p_0];
            map<long long, int>::iterator it = mm.find(p_1);
            if (mm.end() == it) mm[p_1] = 1;
            else ++it->second;
        }
        long long tt;
        for (map<long long, map<long long, int> >::iterator it_0 = m.begin(); 
             it_0 != m.end(); ++it_0) {
            for (map<long long, int>::iterator it_1 = it_0->second.begin();
                 it_1 != it_0->second.end(); ++it_1) {
                c = it_0->first/mult_1;
                b = it_0->first%mult_1;
                a_0 = it_1->first/mult_2;
                tt = it_1->first % mult_2;
                a_1 = tt/mult_1;
                tt %= mult_1;
                a_2 = tt /mult_0;
                a_3 = tt % mult_0; 
                printf("%02lld %08lld %04lld %04lld %04lld %04lld %d\n", 
                       c, b, a_0, a_1, a_2, a_3, it_1->second);
            }
        }
        printf("\n");
    }
}