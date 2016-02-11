

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
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int X, Y;
        cin >> X >> Y;
        if (X != Y && X-2 != Y) {
            cout << "No Number" << endl;   
            continue;
        }        
        
        int dx = 0; 
        if (X % 2 != 0) {
            dx -= 1;
        }
        cout << X + Y + dx << endl;
    }
}

