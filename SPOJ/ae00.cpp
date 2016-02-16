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
    int N;
    cin >> N;
    
    int n = sqrt(N);
    int res = 0;
    for (int k = 1; k <= n; ++k) {
        res += N/k - k + 1;
    }
    cout << res << endl;
}
