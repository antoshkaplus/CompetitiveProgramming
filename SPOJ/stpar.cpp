
#include <iostream>
#include <stack>
#include <queue>

using namespace std;


int main(int argc, const char * argv[]) {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        queue<int> line;
        for (int i = 0; i < n; ++i) {
            int m;
            cin >> m;
            line.push(m);
        }
        stack<int> st;
        int cur = 1;
        // what item we are looking for
        while (cur <= n) {
            
            if (!line.empty() && cur == line.front()) {
                line.pop();
                ++cur;
                continue;
            }
            if (!st.empty() && cur == st.top()) {
                st.pop();
                ++cur;
                continue;
            }
            if (line.empty()) break;
            st.push(line.front());
            line.pop();
        }
        cout << (cur <= n ? "no" : "yes") << endl;
    }
}