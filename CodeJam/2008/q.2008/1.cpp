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

int main(int argc, char* argv[]) {
    int N; 
    string str;
    getline(cin, str);
    N = atoi(str.c_str());
    for (int n = 0; n < N; ++n) {
        int S;
        getline(cin, str);
        S = atoi(str.c_str());
        map<string, int> engines;
        for (int s = 0; s < S; ++s) {
            getline(cin, str);
            engines[str] = s;
        }
        vector<bool> used_engines(engines.size(), false);
        int used_count = 0;
        int Q;
        int result = 0;
        getline(cin, str);
        Q = atoi(str.c_str());
        for (int q = 0; q < Q; ++q) {
            getline(cin, str);
            if (used_count == engines.size()-1 && !used_engines[engines[str]]) {
                // need switch 
                ++result;
                // that engine was first
                fill(used_engines.begin(), used_engines.end(), false);
                used_engines[engines[str]] = true;
                used_count = 1;
            } else {
                if (!used_engines[engines[str]]) {
                    used_engines[engines[str]] = true;
                    ++used_count;
                }
            }
        }
        cout << "Case #" << n+1 << ": " << result << endl;
    }
}