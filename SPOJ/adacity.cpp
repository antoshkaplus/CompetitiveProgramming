




int main() {
    int test_count;
    cin >> test_count;
    for (auto test = 0; test < test_count; ++test) {
        int N, M, F, T;
        cin >> N >> M >> F >> T;
        // N cities, F friends
        vector<Count> from(N, 0);
        vector<Count> to(N, 1);
        for (auto i = 0; i < F; ++i) {
            int city;
            cin >> city;
            ++from[city]; 
        }
        
        MaxBipartiteMatching bm(from, to);

        // M roads
        FloydWarshall<int> fw(N);
        for (auto i = 0; i < M; ++i) {
            int A, B, L;
            cin >> A >> B >> L;
            if (fw.Dist(A, B) < L) continue;
            
            fw.AddDirectedDist(A, B, L);
			fw.AddDirectedDist(B, A, L);
        }
        fw.Compute();
        
        for (auto from_i = 0; from_i < N; ++from_i) {
            for (auto to_i = 0; to_i < N; ++to_i) {
                if (!fw.Exists(from_i, to_i) || fw.Dist() > T) continue;
                bm.addDirEdge(from_i, to_i, fw.Dist(from_i, to_i, from[from_i]));
            }
        }
		
		auto matching = bm.Compute();
		set<int> s;
		for (auto& m : matching) {
			s.insert(m.to);
		}
		cout << s.size() << endl;
    }

}
