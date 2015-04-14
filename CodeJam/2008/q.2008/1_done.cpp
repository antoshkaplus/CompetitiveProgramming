//
//  1.cpp
//  
//
//  Created by Anton Logunov on 8/4/14.
//
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>


using namespace std;

// could pass an iterator and process online
int CountSwitches(const vector<string>& engines, const vector<string>& queries) {
	vector<bool> used_engines(engines.size(), false);
	map<string, int> m;
	for (int i = 0; i < engines.size(); ++i) {
		m[engines[i]] = i;
	}
	int used_count = 0;
	int switch_count = 0;
	for (auto& q : queries) {
		engine_index = m[q];
		if (used_count == engines.size()-1 && !used_engines[engine_index]) {
			++switch_count;
			fill(used_engines.begin(), used_engines.end(), false);
			used_engines[engine_index] = true;
			used_count = 1;
		} else if (!used_engines[engine_index]) { 
			used_engines[engine_index] = true;
			++used_count;
		}
	}
	return switch_count;
}

int main(int argc, char* argv[]) {
    int N; 
    string str;
    getline(cin, str);
    N = atoi(str.c_str());
    for (int n = 0; n < N; ++n) {
        int S;
        getline(cin, str);
        S = atoi(str.c_str());
        vector<string> engines(S);
        for (int s = 0; s < S; ++s) {
            getline(cin, str);
            engines[str] = s;
        }
		int Q;
		getline(cin, str);
		Q = atoi(str.c_str());
		vector<string> queries
		for (int q = 0; q < Q; ++q) {
			getline(cin, str);
			queries[q] = str;	
		}
		int result = CountSwitches(engines, queries);
        cout << "Case #" << n+1 << ": " << result << endl;
    }
}