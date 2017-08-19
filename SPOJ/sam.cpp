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



struct FloorCar {
    int car;
    int next_play;
    
    FloorCar() {}
    
    FloorCar(int car, int next_play) 
    : car(car), next_play(next_play) {}
    
    // want get max priority queue
    bool operator<(const FloorCar& v) const {
        return next_play < v.next_play;
    }
};


int main(int argc, char **argv) {
    int H;
    cin >> H;
    for (int h = 0; h < H; ++h) {
        // N - total of cars
        // K - max cars of the floor
        // P - how many to play 
        int N, K, P;
        cin >> N >> K >> P;
        vector<int> play(P);
        for (auto& p : play) {
            cin >> p;
            --p;
        }
        vector<int> car_prev_play(N, numeric_limits<int>::max());
        vector<int> next_time_play(P);
        // fill next time play backward
        for (auto i = P-1; i >= 0; --i) {
            next_time_play[i] = car_prev_play[play[i]];
            car_prev_play[play[i]] = i;
        }
        // gives you one with maximum
        set<FloorCar> floor_cars;
        vector<bool> on_floor(N, false);
        
        int res = 0;
        for (auto p_i = 0; p_i < play.size(); ++p_i) {
            if (on_floor[play[p_i]]) {
                // car is on the floor but has to update timestamp
                floor_cars.erase(floor_cars.cbegin());
            } else {
                ++res;
                if (floor_cars.size() == K) {
                    auto fc = *floor_cars.crbegin();
                    floor_cars.erase(std::prev(floor_cars.end()));
                    on_floor[fc.car] = false;
                }
                on_floor[play[p_i]] = true;
            }
            floor_cars.emplace(play[p_i], next_time_play[p_i]);
        }
        cout << res << endl;
    }
}
