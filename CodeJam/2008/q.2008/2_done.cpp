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


// forward means from A to B
struct Trip {
    Trip(bool b, int from, int to) 
        : forward(b), from_time(from), to_time(to) {}
    bool forward;
    int from_time;
    int to_time;
	
    // to get minimum time first in max priority_queue
    bool operator<(const Trip& t) const {
        return from_time > t.from_time;
    }
};

// very good idea with time computation
int ReadTime() {
    int h, m;
    char ch;
    cin >> h >> ch >> m;
    return h*60 + m;
}

struct TrainCount {
	int start_from_A {0};
	int start_from_B {0};
}

using TrainQueue = priority_queue<int, std::vector<int>, std::greater<int>>;

TrainCount CountTrains(priority_queue<Trip> table, int turnaround_time) {
	TrainQueue on_A;
	TrainQueue on_B;
	TrainQueue *from_trains, *to_trains;
	TrainCount count;
	int *n_from;
	while (!table.empty()) {
		auto t = table.top();
		table.pop();
		if (t.is_forward) {
			from_trains = &on_A;
			to_trains = &on_B;
			n_from = &count.start_from_A;
		} else {
			from_trains = &on_B;
			to_trains = &on_A;
			n_from = &count.start_from_B;
		}
		if (from_trains->empty()) {
			++(*n_from);
		} else {
			auto time = from_trains->top();
			if (time > t.from_time) {
				++(*n_from);
			} else {
				from_trains->pop();
			}
		}
		to_trains->emplace(t.to_time + turnaround_time);
	}
	return count;
}



int main(int argc, char* argv[]) {
    int N; 
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int T;
        cin >> T;
        int NAtoB, NBtoA;
        cin >> NAtoB >> NBtoA;
        // time table
		priority_queue<Trip> table;
        for (auto n = 0; n < NAtoB; ++n) {
            table.emplace(true, ReadTime(), ReadTime());
        }
        for (auto n = 0; n < NBtoA; ++n) {
            table.emplace(false, ReadTime(), ReadTime());
        }
        TrainCount count = CountTrains(table, T);
        cout << "Case #" << n+1 << ": " << count.start_from_A << " " << count.start_from_B << endl;
    }
}















