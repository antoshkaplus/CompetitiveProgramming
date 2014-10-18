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

class TaroGrid {
public:
    int getNumber(vector<string> str) {
        int maxCount = 0;
        for (int c = 0; c < str.size(); ++c) {
            int count = 1;
            for (int r = 1; r < str.size(); ++r) {
                if (str[r][c] == str[r-1][c]) {
                    ++count;
                } else {
                    if (maxCount < count) maxCount = count;
                    count = 1;
                }
                
            }
        }
        return maxCount;
    }
};

