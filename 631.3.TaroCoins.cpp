#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using Long = int64_t;

class TaroCoins {
public:
    vector<bool> v;
    map<pair<int, bool>, Long> cache;

    Long ways(int currentIndex, bool hasSuchCoin) {
        pair<int, bool> p = {currentIndex, hasSuchCoin};
        if (cache.count(p) == 0) {
            Long r;
            if (v[currentIndex]) {
                r = ways(currentIndex - 1, false);
                if (hasSuchCoin) {
                    r += ways(currentIndex - 1, true);
                }
            } else {
                r = ways(currentIndex - 1, true);
            }
            cache[p] = r;
        }
        return cache[p];
    }

    Long getNumber(Long n) {
        while (n != 0) {
            v.push_back(n%2 == 1);
            n/=2; 
        }
        cache[{0, true}] = 1;
        cache[{0, false}] = v[0] ? 0 : 1;
        return ways(v.size()-1, true);
    }
};

