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

// last position is just for XOR operation.
// everything past this position can be written to last one
int N_MAX = 11;
int MODULO = 100000007;

// we init with 0
array<int, 1 << N_MAX> res, cur;

int shrink(int r) {
	bitset<N_MAX> t;
	t.flip();
	int k = (int)t.to_ulong();
	return k | r;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N, M;
		cin >> N >> M;
		// take uint?
		vector<int> ns = ReadVector(N);
		vector<int> ms = ReadVector(M);
		res.fill(0);
		for (auto n : ns) {
			cur.fill(0);
			for (auto i = 0; i < cur.size(); ++i) {
				if (res[i] != 0) {
					int f = shrink(i^n);
					cur[f] += res[i];
				}
			}
			++res[n];
			for (auto i = 0; i < cur.size(); ++i) {
				res[i] += cur[i];
				res[i] %= MODULO;
			}
		}
		res[0] += 1; // count empty set now
		for (auto m : ms) {
			res[m] = 0;
		}
		int r = 0;
		for (auto s : res) {
			r += s;
			r %= MODULO;
		}
 		cout << "Case " << t+1 << ": " << r << endl; 
	}
}
