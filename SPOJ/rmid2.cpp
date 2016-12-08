
#include <queue>
#include <iostream>
#include <functional>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto test = 0; test < T; ++test) {
        priority_queue<int, std::vector<int>, std::less<int>> p_max;
        priority_queue<int, std::vector<int>, std::greater<int>> p_min;
        for (;;) {
            int n; 
            cin >> n;
            
            if (n == 0) break;
            
            if (n == -1) {
                if (p_min.size() == p_max.size()) {
                    cout << p_max.top() << endl;
                    p_max.pop();
                } else {
                    cout << p_min.top() << endl;
                    p_min.pop();
                }
                
            } else { 
                // positive - insert
                // size of p_min should be not less than p_max
                // p_min is greater than p_max
                
                if (p_min.size() == p_max.size()) {
                    // we should increase size of p_min
                    if (p_min.size() != 0 && n <= p_max.top()) {
                        p_max.push(n);
                        p_min.push(p_max.top());
                        p_max.pop();
                    } else {
                        p_min.push(n);
                    }
                } else {
                    // invariant is there
                    // we should make equal now
                    if (p_max.size() == 0 || n <= p_max.top()) {
                        p_max.push(n);
                    } else {
                        p_min.push(n);
                        p_max.push(p_min.top());
                        p_min.pop();
                    }
                }
            }
        }
    }
}