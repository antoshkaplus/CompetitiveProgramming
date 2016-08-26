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
 
const int MAX_NODES = 100010;


// don't want to read directed tree.
// instead rely on visit once flag
bool visited[MAX_NODES] = {false};
 
const int DIVISOR = 10007;
 
struct R {
	optimal_light_count;
	placement_count;

 	void Add(const R& r) {
		optimal_light_count += r.optimal_light_count;
		placement_count *= r.placement_count;
		placement_count %= DIVISOR;
	}
};
 
const R UNKNOWN{-1,-1};
R table[MAX_NODES][2]; 

// change unknonwn to another type
 
R merge(const R& r_1, const R& r_2) {
	R r = min(r_1, r_2, [](const R& r_1, const R& r_2) { return r_1.optimal_light_count < r_2.optimal_light_count; });
	if (r_1.optimal_light_count == r_2.optimal_light_count) {
		r.placement_count += r_2.placement_count;
	} 
	return r;
} 
 

 
R CountMinVertexConver(int root, bool colored) {
	visited[root] = true;
	if (table[root] != UNKNOWN) {
		return table[root];
	}
	
	// color of this node is predefined. 
	// so number of possibilities is 1
	auto root_r;
	root_r.optimal_light_count = 0;
	root_r.placement_count = 1;
	for (auto a : adjacent(root)) {
		if (visited[a]) continue;
		// we check how many we can get if adj node has another coloring
		auto r = CountMinVertexCover(a, !colored);
		// maybe if we try to color this node we get better result
		if (colored) {
			auto r_2 = CountMinVertexCover(a, colored);
			// ok now we should merge this two results.
			// could do it like a method
			r = merge(r, r_2);
		}
		root_r.Add(r);
	}	
	if (colored) {
		++root_r.optimal_light_count;
	}
	return table[root][colored] = root_r;
}
 

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;
		NodeAdjacencyList adj_list(N);
		for (auto i = 0; i < N-1; ++i) {
			Index n_1, n_2;
			cin >> n_1 >> n_2;
			adj_list[n_1].push_back(n_2);
			adj_list[n_2].push_back(n_1);
		}
		R r = CountMinVertexCover(0);
		cout << r.optimal_light_count << ' ' << r.placement_count % DIVISOR << endl;	
	}
	
	
} 
 
