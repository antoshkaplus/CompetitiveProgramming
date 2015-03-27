
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

// odd false
// even true

// > true
// < false

struct Point {
    bool x;
    bool y;
};

inline Point even(int x, int y) {
    return {!(x & 1), !(y & 1)};
}
inline Point pos(int x, int y) {
    return {x > 0, y > 0};
}

#define NOT_XOR(a, b) (!((a)^(b)))

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T, N;
    const int kMaxN = 30000;
    
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        unsigned long long A[2][2][2][2];
        fill_n(***A, 16, 0);

        cin >> N;
        int x, y;
        for (auto i = 0; i < N; ++i) {
            cin >> x >> y;
            if (x == 0 || y == 0) continue;
            Point p_even = even(x, y);
            Point p_pos = pos(x, y);
            ++A[p_pos.x][p_pos.y][p_even.x][p_even.y];
        }
        
        unsigned long long r = 0;
        for (auto a0 : {true, false}) {
            for (auto a1 : {true, false}) {
                for (auto b0 : {true, false}) {
                    for (bool b1 : {true, false}) {
                        
                        bool ab = NOT_XOR(a0|b1, a1|b0);
                        for (auto c0 : {true, false}) {
                            for (auto c1 : {true, false}) {
                                bool abc = NOT_XOR(NOT_XOR(ab, (b0|c1)), (b1|c0));
                                
                                for (auto d0 : {true, false}) {
                                    for (auto d1 : {true, false}) {
                                        if (NOT_XOR( 
                                                NOT_XOR( 
                                                    NOT_XOR( 
                                                        NOT_XOR(abc, c0|d1), 
                                                    (c1|d0)),
                                                (d0|a1)), 
                                            (a0|d1))) {
                                            
                                            r += A[1][1][a0][a1]*A[1][0][b0][b1]
                                                *A[0][0][c0][c1]*A[0][1][d0][d1];
                                        }
                                    }
                                }       
                            }
                        }       
                    }
                }   
            }
        }
        cout << r << endl;
    }
}













