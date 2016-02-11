
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
        if (N == 0) break;
        
        string s;
        cin >> s;
        for (auto it = s.begin() + N; it < s.end(); it += 2*N) {
            auto it_2 = it + N;
            reverse(it, it_2);
        }
        int M = s.size() / N;
        string res = "";
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < M; ++j) {
                res += s[j * N + i];
            }
        }
        cout << res << endl;
    }
}





