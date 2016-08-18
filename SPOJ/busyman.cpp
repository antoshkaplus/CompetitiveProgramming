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
    int T;
    cin >> T;
    for (int t_i = 0; t_i < T; ++t_i) {
        int N; 
        cin >> N;
        vector<S> activities(N);
        for (auto& s : activities) {
            cin >> s.a >> s.b;
        }
        
        sort(activities.begin(), activities.end(), [](const S& s_1, const S& s_2) {
            return s_1.b < s_2.b;
        });
        
        int last_activity_ended = 0;
        int can_do = 0;
        for (auto& s : activities) {
            if (last_activity_ended <= s.a) {
                ++can_do;
                last_activity_ended = s.b;
            }
        }
            
        cout << can_do << endl;
    }
}
