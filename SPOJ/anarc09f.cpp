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
#include <fstream>


using namespace std;


struct Item {
	int m;
	int64_t e;
	
	bool operator<(const Item& i) const {
		return e < i.e;
	}
	
};

int64_t ReadNumber(istream& cin) {
    int64_t res = 0;
    string s;
    cin >> s;
    auto pos = s.find('.');
    if (pos == string::npos) {
        res = stoll(s) * 1000;
    } else {
        // check negative with 0 whole part
        auto after = s.size() - pos - 1;
        s.erase(pos, 1);
        res = stoll(s);
        for (auto i = 0; i < 3 - after; ++i) {
            res *= 10;
        }
    }
    return res;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	//ifstream cin("../in.txt"); 
	int test_case = 0;
	for (;;) {
		int N; // missle count
		cin >> N;
		if (N == 0) break;
		++test_case;
		array<int64_t, 2> X, Y;
        X[0] = ReadNumber(cin);
        Y[0] = ReadNumber(cin);
        X[1] = ReadNumber(cin);
        Y[1] = ReadNumber(cin);
	 	int64_t T = ReadNumber(cin);
        int64_t PI = 3141;
		vector<int64_t> m_x(N);
		vector<int64_t> m_y(N);
		for (auto i = 0; i < N; ++i) {
			m_x[i] = ReadNumber(cin);
            m_y[i] = ReadNumber(cin);
		} 
		array<vector<Item>, 2> e;
		// could do this stuff with indices better
		for (auto t = 0; t < 2; ++t) {
            e[t].resize(N);
			for (auto i = 0; i < N; ++i) {
                auto d_1 = X[t] - m_x[i];
                auto d_2 = Y[t] - m_y[i];
                auto d = d_1*d_1 + d_2*d_2;
                // those are multiplyed by 1000 more
				e[t][i] = {i, PI*d};
			}
			sort(e[t].begin(), e[t].end());
		}
        // to match area energy
        T *= 1000000;
		
		int best = 0;
		for (auto i = 0; i <= N; ++i) {
            vector<bool> taken(N, false);
            
            auto left = T;
			if (i != 0) {
				left -= e[0][i-1].e;
			}
			if (left < 0) break;
            
            for (auto j = 0; j < i; ++j) {
                taken[e[0][j].m] = true;
            }
            for (auto j = 0; j < N && left >= e[1][j].e; ++j) {
                taken[e[1][j].m] = true;
            }
			auto cur = count(taken.begin(), taken.end(), true);
			if (cur > best) {
				best = cur;
			}
		}
		cout << test_case << ". " << N - best << endl;
	}
}
 







