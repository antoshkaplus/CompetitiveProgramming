//
//  1.cpp
//  
//
//  Created by Anton Logunov on 8/4/14.
//
//

#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;


int main(int argc, char* argv[]) {
    
    int T; 
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> unmalted_likes(N);
        stack<int> non_satisfied;
        vector<int> malted(M, -1);
        vector<int> count(M, 0);
        vector<bool> is_malted(N, false); 
        for (int m = 0; m < M; ++m) {
            int K;
            cin >> K;
            for (int k = 0; k < K; ++k) {
                int p, q;
                cin >> p >> q;
                --p; 
                if (q == 1) {
                    malted[m] = p;
                } else {
                    unmalted_likes[p].push_back(m);
                    ++count[m];
                }
            }
        }
        for (int m = 0; m < M; ++m) {
            if (count[m] == 0) {
                non_satisfied.push(m);
            }
        }
        while (!non_satisfied.empty()) {
            auto m = non_satisfied.top();
            if (malted[m] == -1) break;
            non_satisfied.pop();
            
            if (is_malted[malted[m]]) {
                continue;
            } else {
                is_malted[malted[m]] = true;
                for (int mi: unmalted_likes[malted[m]]) {
                    if (count[mi] == 1) {
                        non_satisfied.push(mi);
                    } 
                    --count[mi];
                }
            }
        }
        cout << "Case #" << t+1 << ": ";
        if (non_satisfied.empty()) {
            for (int n = 0; n < N; ++n) {
                cout << is_malted[n] << " ";
            }
        } else {
            cout << "IMPOSSIBLE";
        }
        cout << endl;
        
    }
}













