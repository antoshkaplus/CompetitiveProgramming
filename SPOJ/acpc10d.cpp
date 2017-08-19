
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>


using namespace std;


int main() {
    std::ios_base::sync_with_stdio(false);
    int test = 0;
    for (;;) {
        
        int N;
        cin >> N;
        if (N == 0) {
            break;
        }
        ++test;
        int Ap, Bp, Cp;
        cin >> Ap >> Bp >> Cp;
        Ap = numeric_limits<int>::max();
        Cp += Bp;
        for (auto i = 1; i < N; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            A += min(Ap, Bp);
            B += min(min(min(A, Ap), Bp), Cp);
            C += min(min(B, Bp), Cp);
            
            Ap = A;
            Bp = B;
            Cp = C;
        }
        
        cout << test << ". " << Bp << endl;
    }
}
