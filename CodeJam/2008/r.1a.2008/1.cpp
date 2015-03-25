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


int main(int argc, char* argv[]) {
    
    int N; 
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int K;
        cin >> K;
        vector<int64_t> a(K), b(K);
        for (int k = 0; k < K; ++k) cin >> a[k];
        for (int k = 0; k < K; ++k) cin >> b[k];
   	    sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<int64_t>());
        int64_t s = 0;
        for (int k = 0; k < K; ++k) {
            s += a[k]*b[k];
        }
        cout << "Case #" << n+1 << ": " << s << endl;
    }
}













