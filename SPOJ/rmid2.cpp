#include <queue>
#include <iostream>
#include <functional>

using namespace std;

// good solution
void slow() {
    priority_queue<int, std::vector<int>, std::less<int>> p_max_fst;
    priority_queue<int, std::vector<int>, std::greater<int>> p_min_snd;
    for (;;) {
        int n; 
        cin >> n;
        
        if (n == 0) break;
        
        if (n == -1) {
            if (p_min_snd.size() == p_max_fst.size()) {
                printf("%d\n", p_max_fst.top());
                p_max_fst.pop();
            } else {
                printf("%d\n", p_min_snd.top());
                p_min_snd.pop();
            }
            
        } else { 
            // positive - insert
            // size of p_min_snd should be not less than p_max_fst
            // p_min_snd is greater than p_max_fst
            
            if (p_min_snd.size() == p_max_fst.size()) {
                // we should increase size of p_min_snd
                if (!p_max_fst.empty() && n <= p_max_fst.top()) {
                    p_max_fst.push(n);
                    p_min_snd.push(p_max_fst.top());
                    p_max_fst.pop();
                } else {
                    p_min_snd.push(n);
                }
            } else {
                // invariant is there
                // we should make equal now
                if (n <= p_min_snd.top()) {
                    p_max_fst.push(n);
                } else {
                    p_min_snd.push(n);
                    p_max_fst.push(p_min_snd.top());
                    p_min_snd.pop();
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto test = 0; test < T; ++test) {
        slow();
    }
}