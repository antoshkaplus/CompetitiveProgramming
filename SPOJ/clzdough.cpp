// may need to use long integer	
	
struct Edge {
	int u, v, d;
}
	
int main() {
	int T;
	cin >> T;
	for (auto t = 0; t < T; ++t) {
		int N, C, M;
		cin >> N >> C >> M;
		vector<Edge> edges(M);
		for (auto& e : edges) {
			cin >> e.u >> e.v >> e.d;
		}
		
		FloydWarshall fw(N);
		for (auto& e : edges) {
			fw.addDirectedDist(e.u, e.v, e.d);
			fw.addDirectedDist(e.v, e.u, e.d);
		}
		fw.Compute();
		// one charge distances
		Grid<int> one(N, N);
		auto func = [&](const Position& pos) {
			one[pos] = fw.Dist(pos.row, pos.col);
		};
		one.ForEachPosition(func);
		
		Grid<int> range_cur = one;
		Grid<int> range_new = one;
		
		for (c = 1; c < C; ++c) {
			for (k = 0; k < V; k++) {
				for (i = 0; i < V; i++) {
					for (j = 0; j < V; j++) {
						if (max(range_cur(i, k), one(k, j)) < range_new(i, j)) {
							range_new(i, j) = max(range_cur(i, k), one(k, j));
						}
					}
				}
			}
			range_cur = range_new;
		}
		
		cout << *max_element(range_cur.begin(), range_cur.end()) << endl;
	}
}
