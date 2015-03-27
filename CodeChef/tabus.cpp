
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>

using namespace std;

struct Bus {
    int opt_max_wait;
    int from_station;
    int to_station;
    int from_time;
    int to_time;
};

vector<vector<int>> station_busses;

Bus busses[100000];
int buss_order[100000];

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N, T, M;
    cin >> N >> T >> M;
    // indices of busses
    // busses that go from this station
    station_busses.resize(N);
    int from_station, to_station, from_time, to_time;
    int bs_sz = 0;
    for (int i = 0; i < M; ++i) {
        cin >> from_station >> to_station 
            >> from_time >> to_time;
        if (to_time > T) continue;
        --from_station;
        --to_station;
        station_busses[from_station].push_back(bs_sz);
        busses[bs_sz++] = {numeric_limits<int>::max(),
                            from_station, to_station, 
                            from_time, to_time};
    }
    iota(buss_order, buss_order + bs_sz, 0);
    // buss with smallest from_time first
    sort(buss_order, buss_order + bs_sz, 
         [&] (int i_0, int i_1) {
             return busses[i_0].from_time < busses[i_1].from_time;
         });
    for (auto i = 0; i < station_busses[0].size(); ++i) {
        busses[station_busses[0][i]].opt_max_wait
         = busses[station_busses[0][i]].from_time;
    }
    for (auto i = 0; i < bs_sz; ++i) {
        auto& b = busses[buss_order[i]];
        if (b.opt_max_wait == numeric_limits<int>::max()) continue;
        auto& bs = station_busses[b.to_station];
        for (auto j = 0; j < bs.size();) {
            auto bi = bs[j];
            auto& p = busses[bi];
            if (p.from_time <= b.from_time) {
                swap(bs[j], bs.back());
                bs.pop_back();
                continue;
            }
            if (p.from_time < b.to_time) {
                ++j;
                continue;
            }
            
            int new_max_wait = max(b.opt_max_wait, p.from_time-b.to_time);
            if (new_max_wait < p.opt_max_wait) {
                p.opt_max_wait = new_max_wait;
            }
            ++j;
        }
    }
    int opt = numeric_limits<int>::max();
    for (auto i = 0; i < bs_sz; ++i) {
        if (busses[i].to_station == N-1 && busses[i].opt_max_wait < opt) {
            opt = busses[i].opt_max_wait;
        }
    }
    cout << (opt != numeric_limits<int>::max() ? opt : -1) << endl;
    
}

















