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
#include <fstream>
#include <array>


using namespace std;
 
 
using Index = int; 
 
template<class T>
using AdjacencyList = std::vector<std::vector<T>>;
using NodeAdjacencyList = AdjacencyList<Index>; 
 
const int MAX_NODES = 100000;
const int UNKNOWN = -1;

array<array<Index, 2>, MAX_NODES> table; 

NodeAdjacencyList adj_list;

const vector<Index>& adjacent(int v) {
    return adj_list[v];
} 
 
 
int CountMinVertexCover(int root, int from, bool colored) {
	if (table[root][colored] != UNKNOWN) {
		return table[root][colored];
	}
	int root_count = 0;
	for (auto a : adjacent(root)) {
		if (a == from) continue;
		auto a_count = CountMinVertexCover(a, root, !colored);
		// maybe if we try to color this node we get better result
		if (colored) {
			auto a_count_2 = CountMinVertexCover(a, root, colored);
			a_count = min(a_count, a_count_2);
		}
		root_count += a_count;
	}
	if (colored) {
		++root_count;
	}
	return table[root][colored] = root_count;
}


void solve(istream& cin, ostream& cout) {
    int N;
    cin >> N;
    int result;
    if (N == 1) {
        result = 1;
    } else {
        adj_list.resize(N);
        table.fill({{UNKNOWN, UNKNOWN}});
        for (auto i = 0; i < N-1; ++i) {
            Index n_1, n_2;
            cin >> n_1 >> n_2;
            --n_1;
            --n_2;
            adj_list[n_1].push_back(n_2);
            adj_list[n_2].push_back(n_1);
        }
        result = min(CountMinVertexCover(0, -1, true), CountMinVertexCover(0, -1, false));
    }
    cout << result << endl;
}



int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
    ifstream cin("../in.txt");
    solve(cin, cout);
} 
 
