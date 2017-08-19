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
#include <fstream>

using namespace std;



template<class T>
std::vector<int> LIS(const std::vector<T>& arr ) {
    std::vector<int> lis(arr.size(), 1);
    
    for (int i = 1; i < arr.size(); i++ ) {
        for (int j = 0; j < i; j++ ) {
            if ((arr[i] > arr[j]) && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    
    int max_end = max_element(lis.begin(), lis.end()) - lis.begin();
    int max = lis[max_end];
    std::vector<int> res(max);
    
    // backtracking to fill res with indexes
    int cur = max;
    int cur_elem = arr[max_end];
    res[cur-1] = max_end;
    for (int i = max_end-1; i >= 0; --i) {
        if (lis[i] == cur-1 && arr[i] < cur_elem) {
            --cur;
            res[cur-1] = i;
            cur_elem = arr[i];
        }
    }
    
    return res;
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> numbs(N);
    for (auto& n : numbs) {
        cin >> n;
    }
    cout << LIS(numbs).size() << endl;
}
