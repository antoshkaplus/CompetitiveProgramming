
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

using namespace std;


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N; 
    cin >> N;
    int c_1_4 = 0;
    int c_1_2 = 0;
    int c_3_4 = 0;
    char ch;
    for (int n = 0; n < N; ++n) {
        int i_0, i_1;
        cin >> i_0 >> ch >> i_1; 
        if (i_0 == 1) {
            if (i_1 == 2) {
                ++c_1_2;
            } else {
                ++c_1_4;
            }
        } else {
            ++c_3_4;
        }
    }
    int res = 0;
    int m = min(c_1_4, c_3_4);
    c_1_4 -= m;
    c_3_4 -= m;
    res += m;
    if (c_3_4 > 0) {
        res += c_3_4;
    }
    res += c_1_2 / 2;
    // halfs and quoters left
    m = c_1_2 %= 2;
    if (m != 0) {
        c_1_4 -= 2;
        ++res;
    }
    if (c_1_4 > 0) {
        res += c_1_4 / 4;
        m = c_1_4 % 2;
        res += (m == 0 ? 0 : m);
    }
    ++res;
    cout << res << endl;
}





