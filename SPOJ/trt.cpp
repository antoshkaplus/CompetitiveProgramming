
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

// first is 0 last is N-1
vector<int> vs;
vector<vector<int>> table;


int BestScore(int i, int j, int age) {
    if (i == j) return vs[i]*age;
    if (table[i][j] > 0) {
        return table[i][j];
    }
    auto score = max(BestScore(i, j-1, age+1) + vs[j]*age, 
                     BestScore(i+1, j, age+1) + vs[i]*age);
    table[i][j] = score;
    return score;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vs.resize(N);
    for (int n = 0; n < N; ++n) {
        cin >> vs[n];
    }
    table.resize(N, vector<int>(N, -1));
    cout << BestScore(0, N-1, 1) << endl;
}

