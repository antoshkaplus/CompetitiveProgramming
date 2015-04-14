#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct DifferentStrings {

    int minimize(string A, string B) {
        int kmin = numeric_limits<int>::max();
        for (int i = 0; i <= B.size()-A.size(); ++i) {
            int k = 0;
            for (int j = 0; j < A.size(); ++j) {
                if (A[j] != B[i+j]) {
                    ++k;
                }
            }
            if (k < kmin) kmin = k;
        }
        return kmin;
    }

};