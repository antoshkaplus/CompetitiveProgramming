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

struct R {
    int st, end, pr;
};


struct S {
    int end;
    int total;
    
    bool operator<(const S& s) const {
        return end < s.end;
    }
};




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T; 
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<R> orders(N);
        for (auto& r : orders) {
            cin >> r.st >> r.end >> r.pr;
            r.end += r.st;
        } 
        sort(orders.begin(), orders.end(), [](const R& r_1, const R& r_2){
            return r_1.end < r_2.end;
        });
        
        vector<S> optimal;
        for (auto& r : orders) {
            S s;
            s.end = r.st;
            // first with greater end
            auto it = upper_bound(optimal.begin(), optimal.end(), s);
            s.end = r.end;
            s.total = r.pr;
            if (it != optimal.begin()) {
                // we can't have another item
                s.total += prev(it)->total;
            }
            if (optimal.empty()) {
                optimal.push_back(s);
                continue;
            }
            if (optimal.back().total >= s.total) {
                continue;
            }
            if (optimal.back().end == s.end) {
                optimal.pop_back();
            }
            optimal.push_back(s);
        }
        cout << optimal.back().total << endl;
    }
    

}
