
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

struct P {
    int r, c;
};

array<P, 4> neigh(P p) {
    return {{{p.r-1, p.c}, {p.r+1, p.c}, {p.r, p.c+1}, {p.r, p.c-1}}};
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int n, m;
        cin >> n >> m;
        vector<string> b(n);
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        vector<vector<int>> dst(n+2, vector<int>(m+2, 1));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (b[r][c] == '1') {
                    dst[r+1][c+1] = 0;
                } else {
                    dst[r+1][c+1] = numeric_limits<int>::max();
                }
            }
        }
        
        queue<P> q;
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= m; ++c) {
                if (dst[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }        
        while (!q.empty()) {
            auto rc = q.front();
            q.pop();
            auto ex = dst[rc.r][rc.c] + 1;
            for (auto& p : neigh(rc)) {
                if (dst[p.r][p.c] > ex) {
                    dst[p.r][p.c] = ex;
                    q.push(p);
                }
            }
        }
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= m; ++c) {
                cout << dst[r][c] << " ";
            }
            cout << endl;
        }
    }
}
