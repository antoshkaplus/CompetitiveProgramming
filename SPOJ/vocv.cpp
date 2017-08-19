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
#include <array>
#include <fstream> 


using namespace std;

using Index = int;

template<class T>
using AdjacencyList = std::vector<std::vector<T>>;

using NodeAdjacencyList = AdjacencyList<Index>;
using Edge = std::array<Index, 2>;
 
const int MAX_NODES = 100010; 
const int DIVISOR = 10007;
 
NodeAdjacencyList adj_list;

const vector<Index>& adjacent(int v) {
    return adj_list[v];
} 

 
struct R {
 	int optimal_light_count;
	int placement_count;

 	void Add(const R& r) {
		optimal_light_count += r.optimal_light_count;
		placement_count *= r.placement_count;
		placement_count %= DIVISOR;
	}
    
    bool operator==(const R& r) {
        return optimal_light_count == r.optimal_light_count && placement_count == r.placement_count;
    }
    
    bool operator!=(const R& r) {
        return !(*this == r);
    }
};
 
const R UNKNOWN{-1,-1};
array<array<R, 2>, MAX_NODES> table; 

// change unknonwn to another type
 
R merge(const R& r_1, const R& r_2) {
	R r = min(r_1, r_2, [](const R& r_1, const R& r_2) { return r_1.optimal_light_count < r_2.optimal_light_count; });
	if (r_1.optimal_light_count == r_2.optimal_light_count) {
		r.placement_count += r_2.placement_count;
	} 
    r.placement_count %= DIVISOR;
	return r;
} 
 

 
R CountMinVertexCover(int root, int from, bool colored) {
	if (table[root][colored] != UNKNOWN) {
		return table[root][colored];
	}
	// color of this node is predefined. 
	// so number of possibilities is 1
	R root_r;
	root_r.optimal_light_count = 0;
	root_r.placement_count = 1;
	for (auto a : adjacent(root)) {
		if (a == from) continue;
		// we check how many we can get if adj node has another coloring
		auto r = CountMinVertexCover(a, root, !colored);
		// maybe if we try to color this node we get better result
		if (colored) {
			auto r_2 = CountMinVertexCover(a, root, colored);
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
 
void solve(istream& cin, ostream& cout) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        R r;
        if (N == 1) {
            r.optimal_light_count = 1;
            r.placement_count = 1;
        } else {
            table.fill({{UNKNOWN, UNKNOWN}});
            adj_list = NodeAdjacencyList(N);
            for (auto i = 0; i < N-1; ++i) {
                Index n_1, n_2;
                cin >> n_1 >> n_2;
                --n_1;
                --n_2;
                adj_list[n_1].push_back(n_2);
                adj_list[n_2].push_back(n_1);
            }
            r = merge(CountMinVertexCover(0, -1, true), CountMinVertexCover(0, -1, false));
        }
        cout << r.optimal_light_count << ' ' << r.placement_count % DIVISOR << endl;	
    }
} 
 

int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
    ifstream cin("../in.txt");
    solve(cin, cout);
} 
 
