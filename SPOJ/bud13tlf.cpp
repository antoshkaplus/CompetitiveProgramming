

// it doesn't answer the question unfortunately.

const int MODULO = 10007;

struct P {
	int c = 1;
	int n;
};


int main() {
	
	int T;
	cin >> T;
	for (auto t = 0; t < T; ++t) {
		int N, W;
		cin >> N >> W;
		auto ws = ReadVector(N);
		sort(ws.begin(), ws.end());
		// i need to reduce this thing
		vector<P> ps;
		ps.emplace(ws.front());
		for (int i = 1; i < ws.size(); ++i) {
			if (ws[i] == ws[i-1]) {
				++ps.back().c;
			} else ps.emplace(ws[i]);
		}
		N = ps.size();
		// main grid with stuff
		Grid<int> g(N, W);
		// introduction of new element
		for (int i = 0; i < N; ++i) {
			Grid<int> t(N, W);
			auto p = ps[i];
			int f_1 = 1;
			int f_2 = 1;	
			for (auto k = 1; k <= p.c; ++k) {	
				for (auto n = k-1; n <= i; ++n) {
					f_1 *= (n+1);
					f_2 *= k;
					for (auto w = 0; w < W; ++w) {
						t(n, w) = g(n - k, w - k*p.n) * f_1 / f_2;
					}
				}
			}
			auto sum = [&](const Position& p) { g[p] += t[p]; };
			g.ForEachPosition(sum);
		}
		auto s = 0;
		// don't forget modulo guys
		auto sum = [&](const Position& p) { s += g[p]; };
		g.ForEachPosition(sum);
		cout << s << endl;
	}
	
}
