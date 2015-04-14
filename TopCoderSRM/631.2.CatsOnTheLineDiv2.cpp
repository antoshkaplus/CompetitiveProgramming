#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class CatsOnTheLineDiv2 {

struct P {
    int p;
    int c;
    
    bool operator<(const P& pp) {
        return p < pp.p;
    }
} 

public:
string getAnswer(vector<int> position, vector<int> count, int time) {
    vector<P> ps;
    for (int i = 0; i < position.size(); ++i) {
        ps.push_back({position[i], count[i]});
    }
    
    sort(ps.begin(), ps.end());
    int next = -1000000;
    for (int i = 0; i < ps.size(); ++i) {
        int start = max(next, ps[i].p - time);
        next = start + ps[i].c;
        if (next - 1 > ps[i].p + time) {
            return "IMPOSSIBLE";
        }
    }
    return "POSSIBLE";
}

};