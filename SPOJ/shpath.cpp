

#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>


using namespace std;

const int n_max = 10000;
const int r_max = 100;

struct {
    bool visited;
    int dist;
    vector<pair<int, int> > graph;
} info[n_max];

pair<int, int> paths[r_max];

struct Item {
    Item(int i, int d) : i(i), d(d) {}	
    Item() {}
    bool operator<(const Item& item) const {
        return d > item.d;
    }
    int i;
    int d;
};

int main(int argc, char **argv) {
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n, r;
        cin >> n;
        map<string, int> names;
        string str;
        for (int i = 0; i < n; ++i) {
            cin >> str;
            names[str] = i;
            int count;
            cin >> count;
            info[i].graph.resize(count);
            for (int j = 0; j < info[i].graph.size(); ++j) {
                cin >> info[i].graph[j].first >> info[i].graph[j].second;
                info[i].graph[j].first -= 1;
            }
        }
        cin >> r;
        string c_0, c_1;
        for (int i = 0; i < r; ++i) {
            cin >> c_0 >> c_1;
            paths[i].first = names[c_0];
            paths[i].second = names[c_1];
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < n; ++j) {
                info[i].visited = false;
                info[i].dist = 2000000;
            }
            info[paths[i].first].dist = 0;
            priority_queue<Item> pq;
            pq.push(Item(paths[i].first, 0));
            int y = i;
            while (!pq.empty()) {
                int i = pq.top().i;
                pq.pop();
                if (i == paths[y].second) break;
                if (info[i].visited) continue;
                info[i].visited = true;
                for (int k = 0; k < info[i].graph.size(); ++k) {
                    int v = info[i].graph[k].first;
                    int alt = info[i].dist + info[i].graph[k].second;
                    if (alt < info[v].dist && info[v].) {
                        info[v].dist = alt;
                        pq.push(Item(v, info[v].dist));
                    }
                }
            }
            cout << info[paths[i].second].dist << endl;
        }
    } 
}