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


// after finding one server with biggest rank we have to find others...

struct Item {
	int d;
	int w

	// highest rank has to go first
	bool operator<(const Item& i) {
		return w < i.w || (w == i.w && r > i.r);
	}
};

int main(int argc, char **argv) {
	int T;
	cin >> T;
	for (auto t = 0; t < T; ++t) {
		int N, M;
		// N - number of servers
		// M - number of wires
		vector<int> ranks(N);
		for (auto& r : ranks) {
			cin >> r;
		}
		vector<Item> adj(N);
		for (int k = 0; k < M; ++k) {
			int i, j, w;
			cin >> i >> j >> w;
			adj[i].push_back({j, w});
			adj[j].push_back({i, w});
		}
		auto storage = 0;
		// for each source node
		for (int s = 0; s < N; ++s) {
			// need to add less comparator as it's minimum queue
			priority_queue<Item> q;
			vector<bool> v(N, false);
			int max_rank = ranks[s];
			// visiting new guy
			auto add = [&](int d) {
				for (auto i : adj[d]) {
					if (!v[i.d]) {
						q.push({i.d, i.w + item.w});
					}
				}
			};
			// 0 until source
			add(s);
			while (!q.empty()) {
				auto item = q.top();
				q.pop();
				auto d = item.d;
				if (v[d]) continue;
				v[d] = true;
				if (max_rank <= ranks[d]) {
					++storage;
				}
				add(item);
			}	
		}
	}
}
