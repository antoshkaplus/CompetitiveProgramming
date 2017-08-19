#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <bitset>

using namespace std;


vector<int> ReadVector(int N) {
    vector<int> res(N);
    for (int& r : res) {
        cin >> r;
    }
    return res;
}


struct S {
    
    template <class T>  
    using V = vector<T>;
    
    V<int> arr; 
    int robin;
    int N;
    
    S(const V<int>& arr, int robin) : arr(arr), robin(robin), N(arr.size()) {
        
    }
    
    int solve() {
        // solve for full sequence
        std::vector<int> lis(N, 1);
        
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if ((arr[i] < arr[j]) && lis[i] < lis[j] + 1) {
                    lis[i] = lis[j] + 1;
                }
            }
        }
        
        int full = *max_element(lis.begin(), lis.end());
        //cout << full << endl;
        
        // check robin stats
        int to_robin = lis[robin];
        //cout << to_robin << endl;
        
        // solve after robin
        fill(lis.begin(), lis.end(), 1);
        for (int i = robin+1; i < N; i++) {
            for (int j = robin+1; j < i; j++) {
                if ((arr[i] < arr[j]) && lis[i] < lis[j] + 1) {
                    lis[i] = lis[j] + 1;
                }
            }
        }
        int after_robin = robin != N-1 ? *max_element(lis.begin(), lis.end()) : 0;
        //cout << after_robin << endl;
        return max(full, to_robin + after_robin);
    }
    
    
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, R;
        cin >> N >> R;
        auto arr = ReadVector(N);
        
        S s(arr, R);
        cout << s.solve() << endl;
    }
}

