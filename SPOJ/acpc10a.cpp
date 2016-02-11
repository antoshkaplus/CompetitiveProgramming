
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


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    for (;;) {
        int i, j, k;
        cin >> i >> j >> k;
        if (i == 0 && j == 0 && k == 0) break;
        if (j-i == k-j) {
            cout << "AP " << k+ j-i << endl;
        } else {
            cout << "GP " << k* j/i << endl;
        }
    }
}


