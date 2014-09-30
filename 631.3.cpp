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
    Long getNumber(Long n) {
        vector<int> v;
        while (n != 0) {
            int b = ((n%2 == 1) ? 1 : 0);
            v.push_back(b);
            n/=2; 
        }
        
        reverse(v.begin(), v.end());
        // how many different 2-th of position value can create
        vector<int> count(v.size());
        vector<int> ones(v.size());
        for (int i = 0; i < v.size(); ++i) {
            if (i == 0) {
                if (v[i] == 1) {
                    count[i] = 0;
                    ones[i] = 1;
                } else {
                    count[i] = 1;
                    ones[i] = 1;
                }
                continue;
            }
            
            if (v[i] == 1) {
                if (count[i-1] > 0) {
                    count[i] = 2;
                    ones[i] = count[i-1] + 1; 
                } else {
                    count[i] = 0;
                    ones[i] = 1;
                }
            } else { // v[i] == 0
                if (count[i-1] > 0) {
                    count[i] = count[i-1] + 1;
                    ones[i] = 1;
                } else {
                    count[i] = 1;
                    ones[i] = 1;
                }
            }
            cerr << v[i] << " " << count[i] << " " << ones[i] << endl;
        }
        Long ans = 1;
        for (int i = 0; i < v.size(); ++i) {
            ans *= ones[i];
        }
        return ans;
    }
};

