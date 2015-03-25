
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
#include <deque>
#include <assert.h>

using namespace std;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N, M;
    const int kMaxN = 1e+6;
    const int kMaxM = 1e+3;
    const int kMod = 1000000007;
    cin >> N >> M;
    //int A[kMaxN];
    //int64_t C[kMaxN];
    
    int *A = new int[kMaxN];
    int *C = new int[kMaxN];
//    
//    for (auto i = 0; i < N; ++i) {
//        cin >> A[i];
//    }
    
    cin >> A[0];
    C[0] = 1;
    int p = 0; // last min turn
    int c = 1; // should be less than modulo guy  
    int c_next = 0;
    int i_start = 0;
    int i_start_next = 1;   
    for (auto i = 1; i < N; ++i) {
        cin >> A[i];
        while (A[i_start] + M < A[i]) {
            c = (c - C[i_start] + kMod)%kMod;
            ++i_start;
            if (i_start == i_start_next) {
                c = c_next;
                c_next = 0;
                i_start_next = i;
                ++p;
            }
        }
        C[i] = c;
        c_next = (c_next + c)%kMod; 
    }
    cout << p << " " << c << endl; 
}













