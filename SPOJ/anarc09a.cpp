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


struct S {

	const string& s;
	vector<vector<int>> t;

	S(const string& s) s(s) {
		// init t
		// columns should be more or same
		int sz = s.size();
		for (auto i = 0; i < sz; ++i) {
			t.push_back(move(vector<int>(sz, -1)));
		}
	}
	
	int solve(int i_1, int i_2) {
		if (i_2 < i_1) return 0;
		
		if (t[i_1][i_2] != -1) {
			return t[i_1][i_2];
		}
		
		int r = numeric_limits<int>::max();
		for (auto i = i_1+1; i <= i_2; i+=2) {
			r = min(r, left_cost(i_1) + right_cost(i) + solve(i_1+1, i-1) + solve(i+1, i_2));
		}
		t[i_1][i_2] = r;
		return r;
	}	
	
	int right_cost(int i) {
		return s[i] == '}' ? 0 : 1;
	}
	
	int left_cost(int i) {
		return s[i] == '{' ? 0 : 1;
	}
};




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	int t = 0;
	for (;;) {
		string str;
		cin >> str;
		if (str.front() == '-') {
			break;
		}
		++t;
		int r = solve(0, str.size()-1);
		cout << t << ". " << r << endl; 
	}
}
 







