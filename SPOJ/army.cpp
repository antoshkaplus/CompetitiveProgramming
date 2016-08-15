
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


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int NG, NM;
        cin >> NG >> NM;
        vector<int> ngs(NG);
        for (auto& n : ngs) cin >> n;
        vector<int> ngs(NM);
        for (auto& n : nms) cin >> n;
        sort(ngs.begin(), ngs.end(), std::greater<int>());
        sort(nms.begin(), nms.end(), std::greater<int>());
        while (!ngs.empty() && !nms.empty()) {
            auto g = ngs.back();
            auto m = nms.back();
            if (g < m) {
                ngs.pop_back();
            } else {
                nms.pop_back();
            }
        }
        if (ngs.empty()) {
            cout << "Mecha";
        }
        cout << "Godzilla" << endl;
    }    
}
