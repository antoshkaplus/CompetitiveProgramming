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
#include <stack>

using namespace std;

struct C {
    int p, w;
};

int kInfinity = numeric_limits<int>::max();

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
	    int E, F;
	    cin >> E >> F;
	    int N;
	    cin >> N;
	    vector<C> cs(N);
	    for (auto& c : cs) {
			cin >> c.p >> c.w;
	    }
	    
	    int M = F - E;
	    // one element for each gram
	    vector<int> ps(M+1, kInfinity);
	    ps[0] = 0;
	    for (int i = 0; i <= M; ++i) {
			for (auto& c : cs) {
				if (i + c.w > M || ps[i] == kInfinity) continue;
				ps[i+c.w] = min(ps[i] + c.p, ps[i+c.w]);
			}
	    }
	    if (ps.back() == kInfinity) {
			cout << "This is impossible." << endl; 
	    } else {
			cout << "The minimum amount of money in the piggy-bank is " 
				 << ps.back() << "." << endl;
	    }
    }
}








