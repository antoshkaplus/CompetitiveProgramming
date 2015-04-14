#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct IncrementingSequence {
    string canItBeDone(int k, vector<int> A) {
        sort(A.begin(), A.end());
        for (int i = 1; i <= A.size(); ++i) {
            int j = -1;
            for (int q = i-1; q < A.size(); ++q) {
                int d = i - A[q];
                if (d < 0 || d%k != 0) {
                    continue;
                }
                j = q;
                break;
            }
            if (j == -1) return "IMPOSSIBLE";
            swap(A[j], A[i-1]);
        }
        return "POSSIBLE";
    }
};