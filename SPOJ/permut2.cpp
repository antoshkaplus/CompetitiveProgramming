
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
    for (;;) {
        int N;
        cin >> N;
        if (N == 0) break;
        vector<int> perm(N);
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
            perm[arr[i] - 1] = i + 1;
        }
        if (arr != perm) {
            cout << "not ";
        }
        cout << "ambiguous" << endl;
    }
}
