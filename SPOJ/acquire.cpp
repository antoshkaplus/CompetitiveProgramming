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

using namespace std;


struct R {
	int w, h;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	
	vector<R> rs(N);
	for (auto& r : rs) {
		cin >> r.w >> r.h;
	}
	
	// inc height, dec width
	sort(rs.begin(), rs.end(), [](const R& r_1, const R& r_2) {
		return r_1.h < r_2.h || (r_1.h == r_2.h && r_1.w > r_2.w);	
	});
	
	// exclude rectangle we don't need 
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j >= 0 && rs[i].w >= rs[j].w) {
			--j;
		}
		++j;
		rs[j] = rs[i];
	}
	// now we can shrink the array
	rs.resize(j+1);
	
	// dynamic prog
	vector<int> cost(N, numeric_limits<int>::max());
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < i-1; ++j) {
			cost[i] = min(cost[i], cost[j] + rs[i].h*rs[j+1].w);
		}
	}
	
	cout << cost.back();
}
