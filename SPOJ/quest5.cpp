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


struct S {
    int a, b;
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int num_tests;
    cin >> num_tests;
    for (int i_test = 0; i_test < num_tests; ++i_test) {
        int num_planks;
        cin >> num_planks;
        vector<S> planks(num_planks);
        for (auto& p : planks) {
            cin >> p.a >> p.b;
        }
        
        sort(planks.begin(), planks.end(), [](const S& s_1, const S& s_2) {
            return s_1.b < s_2.b;
        });
        
        int num_nails = 0;
        int last_nail = -1;
        for (auto& p : planks) {
            if (last_nail < p.a) {
                last_nail = p.b;
                ++num_nails;
            }
        }
        cout << num_nails << endl;
        
    }
}
