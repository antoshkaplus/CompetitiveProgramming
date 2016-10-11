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
#include <fstream>
#include <array>


using namespace std;


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    //ifstream cin("../in.txt");
    
    int N;
    cin >> N;
    vector<int> arr(N);
    vector<bool> negative(N, false);
    
    int a;
    for (int i = 0; i < N; ++i) {
        cin >> a;
        if (a < 0) negative[i] = true;
        arr[i] = abs(a);
    }
    
    vector<int> lis(N, 1);
    
    /* Compute optimized LIS values in bottom up manner */
    for (int i = 1; i < N; i++ ) {
        for (int j = 0; j < i; j++ ) {
            if ((arr[i] > arr[j]) && negative[i] != negative[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
        }
    }
    /* Pick maximum of all LIS values */
    int max_seq = *max_element(lis.begin(), lis.end());
    
    cout << max_seq;    
} 
