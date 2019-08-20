
#include <stack>
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

struct P {
    uint64_t h;
    int c;
    
    P() {}
    P(uint64_t h, int c) : h(h), c(c) {}
    
};

uint64_t max_area = 0;

// returns count of items with high or same height behind
int unwind(stack<P>& st, uint64_t h) {
    int c = 0;
    for (;;) {
        if (st.empty()) break;
        P& p = st.top();
        if (p.h < h) {
            break;
        }
        uint64_t area = p.h * (p.c + c);
        if (area > max_area) {
            max_area = area;
        } 
        st.pop();
        c += p.c;
    }
    return c;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    for (;;) {
        uint64_t N;
        cin >> N;
        if (N == 0) break;
        uint64_t p;
        stack<P> st;
        max_area = 0;
        for (int i = 0; i < N; ++i) {
            uint64_t h;
            cin >> h;
            if (st.empty()) {
                st.emplace(h, 1);
                continue;
            }
            auto& t = st.top();
            if (h > t.h) {
                st.emplace(h, 1);
                continue;
            }
            st.emplace(h, unwind(st, h) + 1);
        }
        unwind(st, 0);
        cout << max_area << endl;
    }
}

