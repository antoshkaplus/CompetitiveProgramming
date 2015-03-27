//
//  1.cpp
//  
//
//  Created by Anton Logunov on 8/4/14.
//
//

#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

struct Item {
    Item(char ch, int count) 
    : ch(ch), count(count) {}
    char ch;
    int count;
}; 


int main(int argc, char* argv[]) {
    
    int T; 
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<vector<Item>> reduced(N);
        string str;
        for (int i = 0; i < N; ++i) {
            auto& red = reduced[i];
            cin >> str;
            red.emplace_back(str[0], 1);
            for (int j = 1; j < str.size(); ++j) {
                if (str[j] == red.back().ch) {
                    ++red.back().count;
                } else {
                    red.emplace_back(str[j], 1);
                }
            }
        }
        
        // check possibility
        bool is_possible = true;
        for (int i = 1; i < N; ++i) {
            if (reduced[0].size() != reduced[i].size()) {
                is_possible = false;
                break;
            }
            for (int j = 0; j < reduced[0].size(); ++j) {
                if (reduced[0][j].ch != reduced[i][j].ch) {
                    is_possible = false;
                    goto go_out;
                } 
            }
        }
        go_out: 
        
        int move_count = 0;
        if (is_possible) {
            for (int j = 0; j < reduced[0].size(); ++j) {
                vector<int> count(N);
                for (int i = 0; i < N; ++i) {
                    count[i] = reduced[i][j].count;
                }
                int a = *min_element(count.begin(), count.end());
                int b = *max_element(count.begin(), count.end());
                auto compute_count = [&](int k) {
                    int value = 0;
                    for (int p : count) {
                        value += abs(k - p);
                    }
                    return value;
                };
                // possible to use fibonacci search
                int best_value = numeric_limits<int>::max();
                for (int c = a; c <= b; ++c) {
                    int value = compute_count(c);
                    if (value < best_value) {
                        best_value = value;
                    }
                }
                move_count += best_value; 
            }
        }
        cout << "Case #" << t+1 << ": ";
        if (is_possible) {
            cout << move_count;
        } else {
            cout << "Fegla Won";
        }
        cout << endl;
    }
}













