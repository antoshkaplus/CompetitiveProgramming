#include <iostream>
#include <vector>
#include <array>
#include <fstream>

using namespace std;

struct P {
    int disk = 0;
    int id;
};


struct SwapCounter {
    
    SwapCounter(const array<vector<vector<P>>, 2>& requestsFrom,
                const array<vector<int>, 2>& depCount) 
    : requestsFrom(requestsFrom), depCount(depCount) {}
    
    // starting disk 0 or 1
    int count(int k, array<vector<int>, 2> ready) {
        auto depCount = this->depCount;
        auto swap = 0;
        auto toInstallCount = depCount[0].size() + depCount[1].size();
        auto& q = ready;
        while (toInstallCount != 0) {
            while (!q[k].empty()) {
                auto i = q[k].back();
                q[k].pop_back();
                --toInstallCount;
                // depCount[k][i] == 0
                for (auto p : requestsFrom[k][i]) {
                    if (--depCount[p.disk][p.id] == 0) {
                        q[p.disk].push_back(p.id);
                    }
                }
            }
            k = !k;
            ++swap;
        }
        return swap+1; // final removal
    }
    
private:
    // 2 disks, each has elements on it. 
    // each element relates to other elements in a way
    // that others require first one to be installed
    const array<vector<vector<P>>, 2>& requestsFrom;
    const array<vector<int>, 2>& depCount;
};


int main() {
    //ifstream cin("../in.txt");
    for (;;) {
        int N_1, N_2, D;
        cin >> N_1 >> N_2 >> D;
        
        if (N_1 == 0 && N_2 == 0 && D == 0) break;
        
        // 2 disks, each has elements on it. 
        // each element has other elements 
        // that depend on installation of the first one
        array<vector<vector<P>>, 2> requestsFrom;
        array<vector<int>, 2> depCount;
        
        requestsFrom[0].resize(N_1);
        requestsFrom[1].resize(N_2);
        depCount[0].resize(N_1, 0);
        depCount[1].resize(N_2, 0);
        
        auto toP = [&](int n) {
            P p;
            if (n > N_1) {
                p.disk = 1;
                n -= N_1; 
            }
            p.id = n-1;
            return p;
        };
        
        for (auto d = 0; d < D; ++d) {
            int x, y;
            // x requires y
            cin >> x >> y;
            auto p_x = toP(x);
            auto p_y = toP(y);
            requestsFrom[p_y.disk][p_y.id].push_back(p_x);
            ++depCount[p_x.disk][p_x.id];
        }
        
        array<vector<int>, 2> ready;
        for (auto i = 0; i < 2; ++i) {
            for (auto j = 0; j < depCount[i].size(); ++j) {
                if (depCount[i][j] == 0) {
                    ready[i].push_back(j);
                }
            }
        }
        
        SwapCounter sc(requestsFrom, depCount);
        cout << min(sc.count(0, ready), sc.count(1, ready)) << endl;
    }
}
