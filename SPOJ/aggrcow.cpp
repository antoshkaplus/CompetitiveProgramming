
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;


template<class P, class Cond>
struct LogicalBinarySearch {
    // we expect integer over here
    static P Min(P a, P b, const Cond& cond) {
        
        auto y_a = cond(a);
        auto y_b = cond(b);
        if (y_a) {
            return a;
        }
        if (!y_b) {
            throw std::runtime_error("no solution");
        }
        
        // y_a is always kept false
        while (b - a > 1) {
            // we want to hit first if two are left
            auto m = (a + b)/2;
            if (cond(m)) {
                b = m;
            } else {
                a = m;
            }
        }
        return b;
    }
    
    static P Max(P a, P b, const Cond& cond) {
        
        auto y_a = cond(a);
        auto y_b = cond(b);
        if (y_b) {
            return b;
        }
        if (!y_a) {
            throw std::runtime_error("no solution");
        }
        
        // y_b is always kept false
        while (b - a > 1) {
            // we want to hit last if two are left
            auto m = (a + b)/2;
            if (cond(m)) {
                a = m;
            } else {
                b = m;
            }
        }
        return a;
        
    }
};



vector<int> ReadVector(int N, istream& cin) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}


// has to be sorted
bool placeable(const vector<int>& xs, int dist, int count) {
    auto cur = -1;
    for (auto x : xs) {
        if (cur == -1 || x - cur >= dist) {
            --count;
            if (count == 0) return true;
            cur = x;
        }
    }
    return false;
}



int main() {
    ifstream cin("../in.txt");
    
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N, C;
        cin >> N >> C;
        auto xs = ReadVector(N, cin);
        sort(xs.begin(), xs.end());
        auto f = [&](int dist) {
            return placeable(xs, dist, C);
        };
        auto ans = LogicalBinarySearch<int, decltype(f)>::Max(1, xs.back()-xs.front(), f);
        cout << ans << endl;
    }
    
    
}
