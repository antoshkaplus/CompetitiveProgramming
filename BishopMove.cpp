#include <algorithm>
#include <stack>

using namespace std;

class BishopMove {
    struct P {
        P(int r, int c) : r(r), c(c) {}
        int r, c;
    };
public:
    int howManyMoves(int r_0, int c_0, int r_1, int c_1) {
        int t[8][8];
        fill_n(*t, 64, -1);
        stack<P> st;
        stack<P> next;
        st.emplace(r_0, c_0);
        t[r_0][c_0] = 0;
        int move = 0;
        while (!st.empty()) {
            while (!st.empty()) {
                auto p = st.top();
                st.pop();
                for (int k = 0; k < 8; ++k) {
                    for (auto pp : {P{p.r + k, p.c + k}, 
                        P{p.r + k, p.c - k}, 
                        P{p.r - k, p.c + k}, 
                        P{p.r - k, p.c - k}}) {
                            if (pp.r >= 0 && pp.r < 8 && pp.c >= 0 && pp.c < 8 &&
                                (t[pp.r][pp.c] == -1)) {
                                t[pp.r][pp.c] = move + 1;
                                next.push(pp);
                            }
                        }
                }
            }
            ++move;
            swap(st, next);
        }
        return t[r_1][c_1];
    }
};