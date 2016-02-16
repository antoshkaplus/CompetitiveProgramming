
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


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    uint64_t n;
    cin >> n;
    if (n == 0 || !(n & (n - 1))) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }
}
