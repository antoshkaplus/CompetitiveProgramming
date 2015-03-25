
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

struct Item {
    int value;
    int count;
};

inline void handle_row(Item* start, Item* finish, int K) {
    // preparing row
    Item* prev = finish - K;
    for (Item* cur = prev+1; cur != finish; ++cur) {
        if (prev->value == cur->value) {
            cur->count += prev->count;
        } else if (prev->value > cur->value) {
            *cur = *prev;
        } 
        prev = cur;
    }
    // go through
    for (Item* item = finish - K - 1; item >= start; --item) {
        Item* cur = item + 1; 
        while(cur != item+K && item->value > cur->value) { 
            *cur = *item;
            ++cur;
        }
        while(cur != item+K && item->value == cur->value) {
            cur->count += item->count;
            ++cur;
        }
        // after that nothing can do
    }
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T; 
    cin >> T; 
    for (auto t = 0; t < T; ++t) {
        int M, N, K;
        const int maxMN = 500;
        Item grid[maxMN][maxMN];
        cin >> M >> N >> K;
        for (auto i = 0; i < M; ++i) {
            for (auto j = 0; j < N; ++j) {
                cin >> grid[i][j].value;
                grid[i][j].count = 1;
            }
        }
        
        for (auto i = 0; i < M; ++i) {
            handle_row(grid[i], grid[i]+N, K);
        }
        
        Item result[maxMN][maxMN];
        Item line[maxMN];
        for (auto j = K-1; j < N; ++j) {
            for (auto i = 0; i < M; ++i) {
                line[i] = grid[i][j];
            }
            
            // prepare line
            handle_row(line, line+M, K);
            for (auto i = K-1; i < M; ++i) {
                result[i-(K-1)][j-(K-1)] = line[i];
            } 
        }
        
        cout << "Case " << t+1 << ":" << endl;
        // write result;
        for (auto i = 0; i < M-K+1; ++i) {
            for (auto j = 0; j < N-K+1; ++j) {
                if (result[i][j].count == 1) {
                    cout << result[i][j].value << " ";
                } else {
                    cout << result[i][j].value << "(" << result[i][j].count << ") ";
                }
            }
            cout << endl;
        }
    }
}













