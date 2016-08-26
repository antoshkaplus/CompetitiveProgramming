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
 
const int MAX_NODES = 100000;
int table[MAX_NODES][2]; 
const int UNKNOWN = -1;
// don't want to read directed tree.
// instead rely on visit once flag
bool visited[MAX_NODES] = {false};
 
 
int CountMinVertexCover(int root, bool colored) {
	visited[root] = true;
	if (table[root] != UNKNOWN) {
		return table[root];
	}
	int root_count = 0;
	for (auto a : adjacent(root)) {
		if (visited[a]) continue;
		auto a_count = CountMinVertexCover(a, !colored);
		// maybe if we try to color this node we get better result
		if (colored) {
			auto a_count_2 = CountMinVertexCover(a, colored);
			a_count = min(a_count, a_count_2);
		}
		root_count += a_count;
	}
	if (colored) {
		++root_count;
	}
	table[root][colored] = root_count;
}


int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	NodeAdjacencyList adj_list(N);
	for (auto i = 0; i < N; ++i) {
		Index n_1, n_2;
		cin >> n_1 >> n_2;
		adj_list[n_1].push_back(n_2);
		adj_list[n_2].push_back(n_1);
	}
	cout << "The set can be {" << CountMinVertexCover(0) << "}" << endl;
} 
 
