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

struct Item {
	int s[2] = {0, 0};
	
	Item() {}
	Item(int s_0, int s_1) {
		s[0] = s_0;
		s[1] = s_1;
	}
	
	Item operator+(const Item& t) const {
		return {s[0]+t.s[0], s[1]+t.s[1]};
	}
};

const Item EMPTY(-1, -1);

const int N_MAX = 30;
int N;
Item t[N_MAX][N_MAX];

function<Item(const Item&,const Item&, int)> comp;

void set_dumb(bool dumb) {
	if (dumb) {
		comp = [](const Item& i_1, const Item& i_2, int p) {
			return i_1.s[0] < i_2.s[0];
		};
	} else { // both are smart
		comp = [](const Item& i_1, const Item& i_2, int p) {
			return i_1.s[p] < i_2.s[p];
		};
	}	
}

vector<int> arr;

void read() {
	cin >> N;
	arr.resize(N);
	for (auto& a : arr) {
		cin >> a;
	}
}

void init() {
	for (auto i = 0; i < N; ++i) {
		for (auto j = 0; j < N; ++j) {
			t[i][j] = EMPTY;
		}
	}
}

// player between 0 and 1 
Item solve(int i, int j, int p) {
	if (i > j) return {0, 0};
	
	if (t[i][j] != EMPTY) {
		return t[i][j];
	}
	
	Item d_i;
	Item d_j;
	d_i[p] = arr[i];
	d_j[p] = arr[j];
	
	auto c = bind(comp, _1, _2, p);
	return t[i][j] = max(solve(i+1, j) + d_i, solve(i, j-1) + d_j, c);
}



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	
	int T;
	cin >> T;
	for (auto t = 0; t < T; ++t) {
		read();
		set_dumb(true);
		init();
		auto r_1 = solve(0, N-1, 0);
		set_dumb(false);
		init();
		auto r_2 = solve(0, N-1, 0);
		cout << r_1 << ' ' << r_2 << endl;
	}
	
}
