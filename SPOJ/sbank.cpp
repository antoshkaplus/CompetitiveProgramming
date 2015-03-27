
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
        
        map<size_t, map<size_t, int> > m;
        size_t p_0, p_1; 
        size_t c, b, a_0, a_1, a_2, a_3;
        const size_t mult_0 = 1e+4;
        const size_t mult_1 = 1e+8;
        const size_t mult_2 = 1e+12;
        
        for (int i = 0; i < n; ++i) {
            cin >> c >> b >> a_0 >> a_1 >> a_2 >> a_3;
            p_0 = c*mult_1 + b;
            p_1 = a_0*mult_2 + a_1*mult_1 + a_2*mult_0 + a_3;
            
            map<size_t, int>& mm = m[p_0];
            map<string, int>::iterator it = mm.find(p_1);
            if (mm.end() == it) mm[p_1] = 1;
            else ++it->second;
        }
        size_t t;
        for (map<size_t, map<size_t, int> >::iterator it_0 = m.begin(); 
             it_0 != m.end(); ++it_0) {
             for (map<int, map<string, int> >::iterator it_1 = it_0->second.begin();
             it_1 != it_0->second.end(); ++it_1) {
                 c = it_0->first/mult_1;
                 b = it_0->first%mult_1;
                 a_0 = it_1->first/mult_2;
                 t = it_1->first % mult_2;
                 a_1 = t/mult_1;
                 t %= mult_1;
                 a_2 = t/mult_0;
                 a_3 = t % mult_0; 
                 printf("%02ld %08ld %04ld %04ld %04ld %04ld %d\n", 
                        c, b, a_0, a_1, a_2, a_3, it_1->second);
            }
        }
        printf("\n");
     }
}