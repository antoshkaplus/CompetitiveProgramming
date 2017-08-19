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


int main() {
	for (;;) {
		int p, q;
		cin >> p >> q;
		cout << p << '+' << q;
		if (!(p == 0 || q == 0 || p == 1 || q == 1)) {
			cout << '!';
		}
		cout << '=' << p + q << endl; 
	}
}
