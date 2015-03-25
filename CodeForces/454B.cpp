
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
    bool found = false;
    int index = -1;
    int first, prev, cur;
    cin >> first;
    prev = first;
    for (int i = 1; i < N; ++i) {
        cin >> cur;
        if (prev > cur) {
            if (index != -1) {
                index = -1;
                break;
            } else {
                found = true;
                index = i;
            }
        }
        prev = cur;
    }
    
    if (!(found && index == -1)) {
        if (prev > first) {
            if (index != -1) {
                index = -1;
            } else {
                found = true;
                index = N;
            }
        }
    }
    
    if (found && index == -1) { // found more than one
        cout << -1;
    } else if (index == -1) { // not found
        cout << 0;
    } else { // found
        cout << N - index;
    }
    
    
}













