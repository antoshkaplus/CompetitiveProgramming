
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
        int N;
        cin >> N;
        vector<int> ms(N);
        vector<int> ws(N);
        for (int& m : ms) {
            cin >> m;
        }
        for (int& w : ws) {
            cin >> w;
        }
        sort(ms.begin(), ms.end());
        sort(ws.begin(), ws.end());
        long res = 0;
        for (int i = 0; i < N; ++i) {
            res += ms[i] * ws[i];
        }
        cout << res << endl;
    }
}

