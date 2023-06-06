#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <stack>
#include <numeric>

using namespace std;

template <typename Index>
using AdjacencyList = std::vector<std::vector<Index>>;

// Source: https://math.stackexchange.com/questions/1871065/euler-path-for-directed-graph
template<class Index>
std::vector<Index> Hierholzer(const AdjacencyList<Index>& adj_list, Index start_v) {
    std::vector<Index> cycle;
    std::stack<Index> st;
    st.push(start_v);

    std::vector<Index> unmarked_start(adj_list.size(), 0);
    while (!st.empty()) {
        auto u = st.top();
        auto i = unmarked_start[u];
        if (i < adj_list[u].size()) {
            auto w = adj_list[u][i];
            st.push(w);
            ++unmarked_start[u];
        } else {
            cycle.push_back(u);
            st.pop();
        }
    }
    if (cycle.size() > 0) {
        cycle.pop_back();
    }
    return cycle;
}


template<class Index>
bool HasEulerianPathDirectedGraph(AdjacencyList<Index> adj_list) {
    Index Vn = adj_list.size();

    std::vector<Index> outdegree(adj_list.size());
    for (auto i = 0; i < adj_list.size(); ++i) {
        outdegree[i] = adj_list[i].size();
    }
    std::vector<Index> indegree(adj_list.size(), 0);
    for (const auto& adj : adj_list) {
        for (auto a : adj) {
            ++indegree[a];
        }
    }

    const auto kInfinity = std::numeric_limits<Index>::max();
    auto an = kInfinity;
    auto bn = kInfinity;
    for (auto i = 0; i < Vn; ++i) {
        if (indegree[i] + 1 == outdegree[i]) {
            if (an != kInfinity) {
                return false;
            }
            an = i;
        }
        else if (indegree[i] == outdegree[i] + 1) {
            if (bn != kInfinity) {
                return false;
            }
            bn = i;
        }
        else if (indegree[i] != outdegree[i]) {
            return false;
        }
    }
    if ((an == kInfinity || bn == kInfinity) && an != bn) {
        // didn't find one of the vertices, but not two
        return false;
    }

    if (an != kInfinity && bn != kInfinity) {
        adj_list[bn].push_back(an);
    }

    Index start_v = kInfinity;
    for (auto i = 0; i < adj_list.size(); ++i) {
        if (adj_list[i].size() > 0) {
            start_v = i;
            break;
        }
    }
    if (start_v == kInfinity) {
        return true;
    }

    auto cycle = Hierholzer(adj_list, start_v);
    auto edges = 0;
    for (auto i = 0; i < adj_list.size(); ++i) {
        edges += adj_list[i].size();
    }
    if (edges != cycle.size()) {
        return false;
    }
    return true;
}


int main() {
    constexpr int N = ('z'-'a') + 1;
    
    int T; // ~500
    cin >> T;
    for (int t = 0; t < T; ++t) {
        AdjacencyList<int> adj(N);
        int M;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            string word;
            cin >> word;
            int s = word.front()-'a';
            int e = word.back()-'a';
            adj[s].push_back(e);
        }
        auto possible = HasEulerianPathDirectedGraph(adj);
        cout << (possible ? "Ordering is possible." : "The door cannot be opened.") << endl;
    }
}


/*
1
1
bc
Ordering is possible
***
1
3
bc
cb
bc
Ordering is possible
***
1
4
bc
cb
bc
cb
Ordering is possible
***
1
4
bc
cd
bc
db
Ordering is possible
***
1
1
zz
Ordering is possible
***
1
2
zz
zz
Ordering is possible
***
1
8
ab
gv
vi
ik
ka
ed
dg
bv
Ordering is possible. Start with 'e'

 // test case
 12
 2
 abcd 
 dcba 
 1
 aa 
 3
 aaa 
 bbb 
 ccc 
 4
 masti 
 ishq 
 bc 
 cb 
 3
 bc 
 cb 
 aa 
 2
 aaa 
 bbb 
 4
 ab 
 bc 
 ca 
 dd 
 3
 ab 
 bc 
 ca 
 6
 ab 
 bc 
 ca 
 zf 
 fg 
 gz
2
acm
ibm
3
acm
malform
mouse
2
ok
ok
*/
