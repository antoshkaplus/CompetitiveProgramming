
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
#include <stack>

using namespace std;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    int half = N/2;
    for (int i = -half; i <= half; ++i) {
        int k = abs(i);
        for (int j = 0; j < k; ++j) {
            cout << "*";
        }
        for (int j = 0; j < N-2*k; ++j) {
            cout << "D";
        }
        for (int j = 0; j < k; ++j) {
            cout << "*";
        }
        cout << endl;
    }    
}













