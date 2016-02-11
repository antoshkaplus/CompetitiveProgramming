
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

using namespace std;

const int N = 100;

int num_sq[N];


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    num_sq[0] = 1;
    num_sq[1] = 5;
    for (int i = 2; i < N; ++i) {
        int n = i+1;
        num_sq[i] = num_sq[i-1] + n*n; 
    }
    int n;
    for (;;) {
        cin >> n;
        if (n == 0) break;
        cout << num_sq[n-1] << endl;
    }
}


