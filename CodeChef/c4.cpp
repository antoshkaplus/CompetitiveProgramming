
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

const int kMaxK = 26;
const int kMaxL = 1000;
const int kMaxS = 500;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T; // guest number
    cin >> T; 
    for (auto t = 0; t < T; ++t) {
        int K; // number of ingridients
        cin >> K; 
        int protein[kMaxK];
        for (auto i = 0; i < K; ++i) {
            cin >> protein[i];
        }
        string sequence;
        cin >> sequence;
        int L = sequence.size(); // how many in sequence
        for (auto i = 0; i < L; ++i) {
            sequence[i] -= 'a';
        }
        int S; // dish protein content
        cin >> S;
        
        // col: protein can be 0 - always possible 
        bool table[kMaxL+1][kMaxS+1];
        for (auto i = 0; i <= S; ++i) {
            table[L][i] = false;
        }
        for (auto i = 0; i <= L; ++i) {
            table[i][0] = true;
        }
        for (auto i = L-1; i >= 0; --i) {
            auto pr = protein[sequence[i]]; 
            copy_n(table[i+1], pr, table[i]);
            for (auto p = pr; p <= S; ++p) {
                table[i][p] = table[i+1][p]|table[i+1][p-pr];
            }
        }
        if (table[0][S] == false) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        
        auto s = S;
        auto p = 0;
        string result = "";
        while (s > 0) {
            auto min_ingridient = K;
            auto min_index = L;
            for (auto i = p; i < L; ++i) {
                auto ingr = sequence[i];
                auto pr = protein[ingr];
                if (s < pr) continue; 
                if (table[i+1][s-pr] && ingr < min_ingridient) {
                    min_index = i;
                    min_ingridient = ingr;
                }
            }
            result += min_ingridient+'a';
            p = min_index+1;
            s -= protein[min_ingridient];
        }
        cout << result << endl;
    }
}













