
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

// start index => how many decodings 
unordered_map<int, uint64_t> m;
string line;

uint64_t countEnc(int startIndex) {
    if (startIndex >= line.size()) return 1;
    if (line[startIndex] == '0') return 0;
    
    auto it = m.find(startIndex);
    if (it != m.end()) {
        return it->second;
    }
    auto next = startIndex + 1;
    auto res = countEnc(next);
    if (next != line.size() && (line[startIndex] == '1' 
                                || (line[startIndex] == '2' && line[next] < '7'))) {
        
        auto p = countEnc(startIndex + 2);
        res += p;
    }
    m[startIndex] = res;
    return res;
}




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    for (;;) {
        getline(cin, line);
        if (line == "0") break;
        cout << countEnc(0) << endl;
        m.clear();
    }
    
}
