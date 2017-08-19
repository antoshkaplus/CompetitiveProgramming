
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Longest {
    int dist = -1;
    int to_root = -1;
    
    bool inited() {
        return !(dist == -1 || to_root == -1);
    }
};

vector<vector<int>> adj;
vector<Longest> tbl;


Longest longDist(int v) {
    auto& ld = tbl[v];
    
    if (ld.inited()) {
        return ld;
    }
    
    if (adj[v].empty()) {
        ld = Longest{0, 0};
    } else {
        auto max_to_root_big = -1;
        auto max_to_root_small = -1; 
        auto max_dist = -1;
        for (auto a : adj[v]) {
            auto t = longDist(a);
            max_dist = max(t.dist, max_dist);
            if (max_to_root_big == -1) {
                max_to_root_big = t.to_root;
            } else if (max_to_root_small < t.to_root) {
                max_to_root_small = t.to_root;
                if (max_to_root_small > max_to_root_big) {
                    swap(max_to_root_big, max_to_root_small);
                }
            }
        }
        ++max_to_root_small;
        ++max_to_root_big;
        ld.to_root = max_to_root_big;
        ld.dist = max(max_to_root_big + max_to_root_small, max_dist);
    }
    return ld;
}

template<class T>
void SwapBackPop(std::vector<T>& v, int i) {
    std::swap(v[i], v.back());
    v.pop_back();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int N;
    cin >> N;
    
    adj.resize(N);
    for (auto i = 0; i < N-1; ++i) {
        int U, V;
        cin >> U >> V;
        adj[U-1].push_back(V-1);
        adj[V-1].push_back(U-1);
    }
    int R; 
    cin >> R; --R;
    
    queue<int> vs;
    vs.push(R);
    while (!vs.empty()) {
        int v = vs.front();
        vs.pop();
        for (auto a : adj[v]) {
            SwapBackPop(adj[a], find(adj[a].begin(), adj[a].end(), v)-adj[a].begin());
            vs.push(a);
        }
    }
    tbl.resize(N);
    int Q;
    cin >> Q;
    for (auto q = 0; q < Q; ++q) {
        int S;
        cin >> S;
        cout << longDist(S-1).dist << endl;
    }
    
    
}
