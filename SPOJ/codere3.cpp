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


int main(int argc, char **argv) {
    
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N;
        cin >> N;
        auto arr = ReadVector(N);
        // inc. lis - how many elements before + this one
        std::vector<int> lis(arr.size(), 1);
        for (int i = 1; i < arr.size(); i++ ) {
            for (int j = 0; j < i; j++ ) {
                if ((arr[i] > arr[j]) && lis[i] < lis[j] + 1) {
                    lis[i] = lis[j] + 1;
                }
            }
        }
        // inc. but from another side
        vector<int> lis_2(arr.size(), 1);
        reverse(arr.begin(), arr.end());
        for (int i = 1; i < arr.size(); i++ ) {
            for (int j = 0; j < i; j++ ) {
                if ((arr[i] > arr[j]) && lis_2[i] < lis_2[j] + 1) {
                    lis_2[i] = lis_2[j] + 1;
                }
            }
        }
        // we have to reverse lis_2 too
        reverse(lis_2.begin(), lis_2.end());
        auto m = 1;
        for (auto i = 0; i < N; ++i) {
            m = max(m, lis[i] + lis_2[i] - 1);
        }
        cout << m << endl;
    }
    
}