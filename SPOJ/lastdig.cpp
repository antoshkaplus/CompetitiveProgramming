// 700 bytes restriction
// using functional programing should help with this


#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

using Array = array<int, 10>;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int A, B;
        cin >> A >> B;
        std::array<int, 10> lol;
        lol.fill(-1);
        int a = A%10;
        int i = 1;
        lol[a] = i;
        for (;;) {
            a = a*A % 10;
            if (lol[a] != -1) break;
            lol[a] = ++i;
        }
        //cout << lol << endl;
        if (B == 0) {
            cout << 1 << endl;
            continue;
        }
        // we found all the info we needed
        if (B < i) {
            int d = find(lol.begin(), lol.end(), B) - lol.begin();
            // this is result
            cout << d << endl;
            continue;
        }
        int k = B % i;
        if (k == 0) k = i;
        //cout << k << endl;
        int d = find(lol.begin(), lol.end(), k) - lol.begin();
        cout << d << endl;
        
    }
}