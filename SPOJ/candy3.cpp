
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
    for (auto t = 0; t < T; ++t) {
        int N;
        cin >> N;
        uint64_t sum = 0;
        for (int i = 0; i < N; ++i) {
            uint64_t cs;
            cin >> cs;
            cs %= N;
            sum += cs;
            sum %= N;
        }
        if (sum == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        
    }
}

