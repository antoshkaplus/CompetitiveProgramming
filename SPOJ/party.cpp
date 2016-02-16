
#include <algorithm>
#include <vector>
#include <iostream>


using namespace std;

int MAX_BUDGET = 500;
int MAX_PARTY_COUNT = 100;


int main() {
    int budget, party_count;
    while (true) {
        cin >> budget >> party_count;
        if (budget == 0 && party_count == 0) {
            break;
        }
        vector<int> vs(budget+1, 0);
        for (int i = 0; i < party_count; ++i) {
            int fee, fun;
            cin >> fee >> fun;
            for (int f = budget; f >= fee; --f) {
                vs[f] = max(vs[f], vs[f-fee]+fun); 
            }
        }
        int k = budget;
        while (k > 0 && vs[k] == vs[k-1]) --k;
        cout << k << " " << vs[k] << endl;
    }    
} 
