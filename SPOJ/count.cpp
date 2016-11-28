<<<<<<< HEAD
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
=======
/*
USER: zobayer
TASK: COUNT
ALGO: dynamic programming
*/

#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <valarray>
using namespace std;

#define DEBUG if(0)
#define PAUSE system("pause")
#define ALL(c) c.begin(), c.end()
#define PB(x) push_back(x)
#define SET(p) memset(p, -1, sizeof(p))
#define CLR(p) memset(p, 0, sizeof(p))
#define BIG(p) memset(p, 0x3f, sizeof(p))
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
#define SZ(c) c.size()

typedef long long i64;
typedef unsigned long long u64;
typedef pair< int, int > pii;

template< class T > T _abs(const T &n) { return (n < 0 ? -n : n); }
template< class T > T _max(const T &a, const T &b) { return (a > b ? a : b); }
template< class T > T _min(const T &a, const T &b) { return (a < b ? a : b); }
template< class T > T gcd(const T a, const T b) { return (b ? gcd<T>(b, a%b) : a); }
template< class T > T lcm(const T a, const T b) { return (a / gcd<T>(a, b) * b); }
template< class T > bool inrange(const T &a, const T &b, const T &c) { return a<=b && b<=c; }
template< class T > T sq(const T &x) { return x * x; }

const double EPS = 1e-10;
const int INF = 0x3f3f3f3f;

const int MAX = 5005;
int memo[MAX][MAX];

int solve(int c, int t) {
	if(memo[c][t]) return memo[c][t] - 1;
	if(t==1) return 1;
	int i, ret = 0;
	for(i=c/t; i>=0; i--) {
		ret += solve(c-i*t, t-1);
		if(ret >= 1988) ret %= 1988;
	}
	return (memo[c][t] = 1 + ret) - 1;
}

int main() {
	int c, t;
	while(scanf("%d%d", &c, &t)==2 && c)
		printf("%d\n", solve(c-t, t));
	return 0;
}
>>>>>>> ec8a3451b39f8bba8e5fb8d95ae0cbb9cf4f0374
