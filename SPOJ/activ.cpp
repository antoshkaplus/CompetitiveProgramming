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
#include <iomanip>


using namespace std;


struct T {
    int s, e;
    
    bool operator<(const T& t) const {
        return s < t.s;
    }
};

struct A {
    
    const vector<T>& ts;
    vector<int> res;
    
    const static int UNKNOWN;
    const static int FACTOR;
    
    A(const vector<T>& ts) : ts(ts) {
        res.resize(ts.size()+1, UNKNOWN);
        res.back() = 1;
    }
    
    int Solve(int i) {
        // i == sz already there 
        if (res[i] != UNKNOWN) {
            return res[i];
        }
        int r = Solve(i+1);
        auto it = lower_bound(ts.begin()+i+1, ts.end(), T{ts[i].e, 0});
        int j = it - ts.begin();
        r += Solve(j);
        res[i] = r;
        res[i] %= FACTOR;
        return res[i]; //(res[i] = r) %= FACTOR;
    }
    
    void Check() {
        for (auto& r : res) {
            if (r >= FACTOR) throw runtime_error("");
        }
    }
};

const int A::UNKNOWN = -1;
const int A::FACTOR = 100000000;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    for (;;) {
        int N;
        cin >> N;
        if (N == -1) {
            break;
        }
        vector<T> ts(N);
        for (auto& t : ts) {
            cin >> t.s >> t.e;
        }
        sort(ts.begin(), ts.end());
        A a(ts);
        int r = a.Solve(0);
        a.Check();
        if (r >= A::FACTOR) throw runtime_error("");
        // have to substract empty set
        //printf("%08d\n", abs(r-1));
        cout << setfill('0') << setw(8) << abs(r-1) << endl;
    }
}
