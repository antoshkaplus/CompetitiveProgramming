#include <vector>
#include <iostream>

using namespace std;

class Fclass {
public:
    vector<int> cache{0, 1};

    int F(int N) {
        if (cache.size() <= N) {
            cache.resize(N+1, -1);
        }
        if (cache[N] != -1) {
            return cache[N];
        }
        return cache[N] = F(N-1) + F(N-2);
    }
};

int Frec(int N) {
    if (N == 0) return 0;
    if (N == 1) return 1;
    return Frec(N-1) + Frec(N-2);
}

int F(int N) {
    if (N <= 1) return N;
    auto n_0 = 0;
    auto n_1 = 1;
    for (auto i = 2; i <= N; ++i) {
        auto n = n_0 + n_1;
        n_0 = n_1;
        n_1 = n;
    }
    return n_1;
}

int main() {
    Fclass f_0;
    cout << f_0.F(10) << endl;
    cout << Frec(10) << endl;
    cout << F(10) << endl;
}
