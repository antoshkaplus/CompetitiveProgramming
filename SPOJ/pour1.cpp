
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

int gcd(int i_0, int i_1) {
    while (i_1 != 0) {
        int r = i_0%i_1;
        i_0 = i_1;
        i_1 = r;
    }
    return i_0;
}

int main(int argc, char **argv) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        std::set<int> s;
        std::queue<pair<int, int> > q; 
        int a, b, c;
        cin >> a >> b >> c;
        int r = -1;
        int g = gcd(a, b); 
        if (g >= 1 && c%g == 0 && (c <= a || c <= b)) {	
            int i = 0;
            int d_a = 0;
            int d_b = 0;
            int buf_a, buf_b;
            while (d_a != c && d_b != c) {
                if (d_b == b) {
                    d_b = 0;
                } else if (d_a == 0) {
                    d_a = a;
                } else {
                    buf_a = d_b + d_a - b;
                    if (buf_a < 0) buf_a = 0;
                    buf_b = d_b + d_a;
                    if (buf_b > b) buf_b = b;  
                    d_a = buf_a;
                    d_b = buf_b;
                }  
                ++i;
            }
            int j = 0;
            d_a = 0;
            d_b = 0;
            swap(a, b);
            while (d_a != c && d_b != c) {
                if (d_b == b) {
                    d_b = 0;
                } else if (d_a == 0) {
                    d_a = a;
                } else {
                    buf_a = d_b + d_a - b;
                    if (buf_a < 0) buf_a = 0;
                    buf_b = d_b + d_a;
                    if (buf_b > b) buf_b = b;  
                    d_a = buf_a;
                    d_b = buf_b;
                }  
                ++j;
            }
            r = min(i, j);
        }
        cout << r << endl;
    } 
}