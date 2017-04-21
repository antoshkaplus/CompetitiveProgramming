#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX = 100; 

int comp_y_2(int y_1, int x_1, int x_2) {
    return x_1 + y_1 - x_2;
} 


int main() {
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int W, H;
        cin >> W >> H;
        
        vector<string> bd(H);
        for (auto& b : bd) cin >> b;
        
        // y_1, x_1, x_2
        int R[MAX][MAX][MAX];
        for (auto y_1 = 0; y_1 < H; ++y_1) {
            for (auto x_1 = 0; x_1 < W; ++x_1) {
                for (auto x_2 = 0; x_2 < W; ++x_2) {
                    auto y_2 = comp_y_2(y_1, x_1, x_2);
                    if (y_2 < 0 || y_2 >= H) continue;
                    
                    auto& r = R[y_1][x_1][x_2] = numeric_limits<int>::min();
                    
                    if (bd[y_1][x_1] == '#' || bd[y_2][x_2] == '#') {
                        continue;
                    }
                    auto cur = 0;
                    if (bd[y_1][x_1] == '*') ++cur;
                    if (bd[y_2][x_2] == '*' && y_2 != y_1 && x_1 != x_2) ++cur;
                    
                    if (x_1 == 0 && y_1 == 0) {
                        r = cur;
                        continue;
                    }  
                    
                    if (y_1 > 0 && y_2 > 0) {
                        r = max(r, cur + R[y_1-1][x_1][x_2]);
                    }
                    if (x_1 > 0 && x_2 > 0) {
                        r = max(r, cur + R[y_1][x_1-1][x_2-1]);
                    }
                    if (y_2 > 0 && x_1 > 0) {
                        r = max(r, cur + R[y_1][x_1-1][x_2]);
                    }
                    if (y_1 > 0 && x_2 > 0) {
                        r = max(r, cur + R[y_1-1][x_1][x_2-1]);
                    }
                }
            }
        }
        
        auto res = 0;
        for (auto y = 0; y < H; ++y) {
            for (auto x = 0; x < W; ++x) {
                res = max(res, R[y][x][x]);
            }
        }
        cout << res << endl;
    }
    
    
}
