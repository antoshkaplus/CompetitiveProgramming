#include <vector>
#include <tuple>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <memory>


int solve(int prev, int cur, char* ch) {
	if (*ch == 0) {
		return prev <= cur ? 1 : 0;
	}
	int r = 0;
	if (prev <= cur) {
		r += solve(cur, *ch - '0', ++ch);
	}
	r += solve(prev, cur + (*ch - '0'), ++ch);
	return r;
}

// i can keep how many possibilities on the right 
// if seq starts at i and ends at j
// we have to carry i around in the function calls
int main() {
	
	int test_case = 0;
	for (;;) {
		
		string s;
		getline(cin, s);
		if (s == "bye") {
			break;
		}
		++test_case;
		cout << test_case << ". " << solve(0, 0, s.c_str()) -1 << endl;
	}
	
}
