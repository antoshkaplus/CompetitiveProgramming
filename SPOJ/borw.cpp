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
    V<V<V<int>>> t;
    int N;
    
    S(const V<int>& arr) : arr(arr) {
        auto& a = this->arr; 
        N = a.size();
        reverse(a.begin(), a.end());
        a.push_back(0);
        reverse(a.begin(), a.end());
        
        t.resize(N+1, V<V<int>>(N+1, V<int>(N+1, -1)));        
    }
    
    // i - last batman
    // j - last batwoman
    // k - current
    int solve(int i, int j, int k) {
        if (k == N+1) {
            return 0;
        }
        
        if (t[i][j][k] != -1) {
            return t[i][j][k];
        }
        
        // no one takes it
        int res = solve(i, j, k+1);
        
        if (i == 0 || arr[i] < arr[k]) {
            res = max(res, solve(k, j, k+1) + 1);
        }
        
        if (j == 0 || arr[j] > arr[k]) {
            res = max(res, solve(i, k, k+1) + 1);
        }
        
        return t[i][j][k] = res;
    }
    
    
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    for (;;) {
        int N;
        cin >> N;
        if (N == -1) break;
        auto arr = ReadVector(N);
        
        // the design is very pure..
        // here we provide array, but current position went as 1
        S s(arr);
        cout << N - s.solve(0, 0, 1) << endl;
    }
}

