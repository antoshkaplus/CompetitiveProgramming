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


inline std::vector<std::string> Split(std::string str, char delim) {
    std::vector<std::string> r;
    Index s_i = 0; // starting index for sustr
    for (Index i = 0; i < str.size(); ++i) {
        if (str[i] == delim) {
            r.push_back(str.substr(s_i, i-s_i));
            s_i = i+1;
        }
    }
    r.push_back(str.substr(s_i));
    return r;
}

vector<int> ReadSeq() {
	string str;
	getline(cin, str);
	vector<string> ss = Split(str, ' ');
	vector<int> s(ss.size());
	transform(ss.begin(), ss.end(), s.begin(), stoi);
	return s;
}

int END = numeric_limits<int>::max();

int main() {
	
	for (;;) {
		
		vector<int> s_1 = ReadSeq();
		if (s_1.size() == 1 && s_1.back() == 0) {
			break;
		}
		vector<int> s_2 = ReadSeq();
		
		s_1.push_back(END);
		s_2.push_back(END);
		
		int i_1 = 0;
		int i_2 = 0;
		
		int sum_1 = 0;
		int sum_2 = 0;
		
		int max_sum = 0;
		for (;;) {
			if (s_1[i_1] == s_2[i_2]) {
				if (s_1[i_1] == END) {
					break;
				}
				max_sum += max(sum_1, sum_2) + s_1[i_1];
				sum_1 = 0;
				sum_2 = 0;
				++i_1;
				++i_2;
			} else if (s_1[i_1] > s_2[i_2]) {
				sum_2 += s_2[i_2];
				++i_2;
			} else { 
				sum_1 += s_1[i_1];
				++i_1;
			}
			
		}
		max_sum += max(sum_1, sum_2);
		cout << max_sum << endl;
	}
	
}
