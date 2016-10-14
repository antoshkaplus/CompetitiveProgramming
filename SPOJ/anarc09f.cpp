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


struct Item {
	int m;
	double e;
	
	bool operator<(const Item& i) {
		return e < i.e;
	}
	
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	
	int test_case = 0;
	for (;;) {
		int N; // missle count
		cin >> N;
		if (N == 0) break;
		++test_case;
		array<double, 2> X, Y;
		cin >> X[0] >> Y[0] >> X[1] >> Y[1] >> T;
		double PI = 3.141;
		vector<double> m_x;
		vector<double> m_y;
		for (auto i = 0; i < N; ++i) {
			cin >> m_x[i] >> m_y[i];
		} 
		
		array<vector<Item>, 2> e;
		// could do this stuff with indices better
		for (auto t = 0; t < 2; ++t) {
			for (auto i = 0; i < N; ++i) {
				auto d = pow(X[t] - m_x[i], 2) + pow(Y[t] - m_y[i], 2);
				e[t][i] = {i, PI*d};
			}
			sort(e[t].begin(), e[t].end());
		}
		
		int best = 0;
		vector<bool> taken = 0;
		// how many we take for first tower
		
		// use boolean and probably something like long long and it should be just fine
		
		for (auto i = 0; i <= N; ++i) {
			int cur = 0;
			auto left = T;
			if (i != 0) {
				left -= e[0][i-1];
			}
			if (left < 0) break;
			cur += i;
			auto it = upper_bound(e[1].begin(), e[1].end(), {-1, left});
			if (it != e[1].begin()) {
				cur += it - e[1].begin();
			}
			if (cur > best) {
				best = cur;
			}
		}
		cout << test_case << ". " << N - best << endl;
	}
}
 







