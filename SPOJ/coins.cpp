
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

using namespace std;

// in this problem we have to use recursion
// as previous problem state is important
// coins => dollars
std::unordered_map<uint64_t, uint64_t> map;

uint64_t convertToDollars(uint64_t c) {
    auto it = map.find(c);
    if (it != map.end()) {
        return it->second;
    }
    auto c_0 = c/2;
    auto c_1 = c/3;
    auto c_2 = c/4;
    
    auto s = (c_0 > 0 ? convertToDollars(c_0) : 0) 
    + (c_1 > 0 ? convertToDollars(c_1) : 0) 
    + (c_2 > 0 ? convertToDollars(c_2) : 0);
    return map[c] = max(s, c);
}




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::string line;
    
    while (std::getline(std::cin, line))
    {
        auto number = stoul(line);
        cout << convertToDollars(number) << endl;
    }
    
}
