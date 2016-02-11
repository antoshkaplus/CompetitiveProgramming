
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
#include <numeric>

using namespace std;


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    for (;;) {
        int N;
        cin >> N;
        if (N == -1) {
            break;
        }
        vector<int> ps(N);
        for (int& p : ps) {
            cin >> p;
        }
        int total = accumulate(ps.begin(), ps.end(), 0);
        int per_p = total / N;
        if (per_p * N != total) {
            cout << -1 << endl;
            continue;
        }
        int moves = 0;
        for (int& p : ps) {
            if (p > per_p) moves += p - per_p;
        }
        cout << moves << endl;
    }
}


