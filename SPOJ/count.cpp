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


const int FACTOR = 1988;

int solve(int P, int N, int K) {
    if (K == 1) {
        return 1;
    }
    int r = 0;
    while (N/P >= K) {
        r += solve(P, N-P, K-1);
        r %= FACTOR;
        ++P;
    } 
    return r;
}



int main(int argc, char **argv) {
    for (;;) {
        int N, K;
        cin >> N >> K;
        if (N == 0 && K == 0) break;
        if (K == 1) cout << 1;
        else {
            auto r = 0;
            for (auto i = 1; i <= N/K; ++i) {
                r += solve(i, N-i, K-1);
            }
            cout << r % FACTOR;
        }
        cout << endl;
    }
}   