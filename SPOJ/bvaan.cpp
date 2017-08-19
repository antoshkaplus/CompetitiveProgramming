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

template<class T>
using V = vector<T>;


vector<int> ReadVector(int N) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}

const int N_MAX = 101;
const int BAD = -256*N_MAX*N_MAX;
const int INIT = -1;

int tt[N_MAX][N_MAX][N_MAX];
string b_1, b_2; 
int K;

int init() {
    auto N_1 = b_1.size();
    auto N_2 = b_2.size();
    for (auto i = 0; i <= N_1; ++i) {
        for (auto j = 0; j <= N_2; ++j) {
            tt[i][j][0] = 0;
            for (auto k = 1; k <= K; ++k) {
                if (i == N_1 || j == N_2) {
                    tt[i][j][k] = BAD;
                } else {
                    tt[i][j][k] = INIT;
                }
            }
        }
    }
}


int solve(int i, int j, int k) {
    if (tt[i][j][k] != INIT) {
        return tt[i][j][k];
    }
    int r = BAD;
    if (b_1[i] == b_2[j]) {
        r = solve(i+1, j+1, k-1) + b_1[i];
    }
    r = max(r, solve(i, j+1, k));
    r = max(r, solve(i+1, j, k));
    r = max(r, solve(i+1, j+1, k));
    return tt[i][j][k] = r;
}



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        cin >> b_1 >> b_2 >> K;
        init();
        cout << max(0, solve(0, 0, K)) << endl;
    }
}