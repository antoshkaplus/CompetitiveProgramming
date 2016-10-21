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


struct T {
	int s, e;
	
	bool operator<(const T& t) {
		return s < t.s;
	}
};

struct A {
	
 	const vector<T>& ts;
	const vector<int> res;
	
	const int UNKNOWN = -1;
	const int FACTOR = 100000000;
	
	A(const vector<T>& ts) ts(ts) {
		res.resize(ts.size()+1, UNKNOWN);
		res.back() = 1;
	}
	
	int Solve(int i) {
		// i == sz already there 
		if (res[i] != UNKNOWN) {
			return res[i];
		}
	  	int r += solve(i+1);
		auto it = lower_bound(ts.begin()+i, ts.end(), {ts[i].e, 0});
		int j = it - ts.begin();
		r += solve(j);
		return res[i] = r%FACTOR;
	}
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	
	for (;;) {
		int N;
		cin >> N;
		if (N == -1) {
			break;
		}
		vector<T> ts(N);
		for (auto& t : ts) {
			cin >> t.s >> t.e;
		}
		sort(ts.begin(), ts.end(), [](const T& t_1, const T& t_2) {
			return t_1.s < t_2.s;
		});
		A a(ts);
		// have to substract empty set
		cout << setfill('0') << setw(8) << a.Solve(0)-1 << endl;
	}
}
