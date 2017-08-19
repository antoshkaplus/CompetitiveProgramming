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
#include <array>
#include <iomanip>
#include <memory>
#include <fstream>
#include <bitset>
#include <cassert>

using namespace std;


class DistinctSubsequenceCounter {
	
 	uint64_t count(string s) {
		int letter_count = 'Z' - 'A' + 1;
		vector<int> letter_last_index_seen(letter_count, -1);
		vector<uint64_t> counts(s.size()+1, 0);
		
		// empty set counts
		counts[0] = 1;
		// i - index+1 of string, how many letters are taken
		for (int i = 1; i <= s.size(); ++i) {
			counts[i] = 2*counts[i-1];
			int index_seen = letter_last_index_seen[s[i-1]-'A']
			if (index_seen != -1) {
				counts[i] -= counts[index_seen]
			}
			letter_last_index_seen[s[i-1]-'A'] = i-1
		}
		return counts.back();
	}
	
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		std::string str;
		cin >> str;
		cout << DistinctSubsequenceCounter().count(str) << endl;
	}
}

