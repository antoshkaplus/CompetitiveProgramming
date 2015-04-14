#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct SubstitutionCode {
    int getValue(string key, string code) {
        map<char, int> encode;
        for (int i = 0; i < code.size(); ++i) {
            encode[code[i]] = i+1;
        }
        int s = 0;
        for (int i = 0; i < key.size(); ++i) {
            auto it = encode.find(key[i]);
            if (it == encode.end()) continue;
            s += it->second;
            s *= 10;
        }
        return s;
    }
};