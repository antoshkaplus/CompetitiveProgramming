//
//  1.cpp
//  
//
//  Created by Anton Logunov on 8/4/14.
//
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// queue is maximum
struct Trip {
    Trip(bool b, int from, int to) 
        : isForward(b), fromTime(from), toTime(to) {}
    bool isForward;
    int fromTime;
    int toTime;
    // to get minimum time first
    bool operator<(const Trip& t) const {
        return fromTime > t.fromTime;
    }
};

int readTime() {
    int h, m;
    char ch;
    cin >> h >> ch >> m;
    return h*60 + m;
}

int main(int argc, char* argv[]) {
    
    int N; 
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int T;
        cin >> T;
        int NAtoB, NBtoA;
        cin >> NAtoB >> NBtoA;
        priority_queue<Trip> table;
        for (auto n = 0; n < NAtoB; ++n) {
            table.emplace(true, readTime(), readTime());
        }
        for (auto n = 0; n < NBtoA; ++n) {
            table.emplace(false, readTime(), readTime());
        }
        priority_queue<int, std::vector<int>, std::greater<int>> Atrains, *fromTrains;
        priority_queue<int, std::vector<int>, std::greater<int>> Btrains, *toTrains;
        int nAtrains = 0;
        int nBtrains = 0;
        int *nFrom;
        while (!table.empty()) {
            auto t = table.top(); 
            table.pop();
            if (t.isForward) {
                fromTrains = &Atrains;
                toTrains = &Btrains;
                nFrom = &nAtrains;
            } else {
                fromTrains = &Btrains;
                toTrains = &Atrains;
                nFrom = &nBtrains;
            }
            
            if (fromTrains->empty()) {
                ++(*nFrom);
            } else {
                auto time = fromTrains->top();
                if (time > t.fromTime) {
                    ++(*nFrom);
                } else {
                    fromTrains->pop();
                }
            }
            toTrains->emplace(t.toTime + T);
        }
        cout << "Case #" << n+1 << ": " << nAtrains << " " << nBtrains << endl;
    }
}















