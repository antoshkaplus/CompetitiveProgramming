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
#include <functional>

using namespace std;


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	
	int T;
	cin >> T;
	for (auto t = 0; t < T; ++t) {
		int N, K;
		cin >> N >> K;
		vector<int> A(K+1, N+1);
		A[0] = 0;
		for (auto i = 0; i < N; ++i) {
			int w;
			cin >> w;
			for (auto j = K; j >= w; --j) {
				A[j] = min(A[j-w]+1, A[j]);
			}
		}
		if (A.back() > N) {
			cout << "impossible";
		} else {
			cout << A.back();
		}
		cout << endl;
	} 	
}
