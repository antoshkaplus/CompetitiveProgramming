#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class S {
public:
    
    S() : counts(11, 0) {}
    
    vector<int> counts;
    
    // returns -1 if no swap possible
    int swap(int d) {
        for (auto i = d+1; i < counts.size(); ++i) {
            if (counts[i] > 0) {
                --counts[i];
                ++counts[d];
                return i; 
            }
        }
        return -1;
    }
    
    void reorder(vector<int8_t>& ds, int start) {
        for (auto i = 0; i < counts.size(); ++i) {
            fill_n(ds.begin()+start, counts[i], i);
            start += counts[i];
        }
    }
    
    bool makeNext(vector<int8_t>& ds) {
        bool found = false;
        // how many of this digit on the right
        for (auto i = (int)ds.size()-1; i >= 0; --i) {
            auto d = swap(ds[i]);
            //cout << (int)ds[i] << " "<< i << endl;
            if (d != -1) {
                ds[i] = d;
                reorder(ds, i+1);
                found = true;
                break;
            }
            ++counts[ds[i]];
        }
        return found;
    }
};


int main() {
    
    int t;
    cin >> t;
    for (auto i = 0; i < t; ++i) {
        int n;
        cin >> n;
        vector<int8_t> ds(n);
        for (auto& d : ds) {
            int p;
            cin >> p;
            d = p;
        }
        S s;
        //for (auto& d : ds) cout << (int)d;
        
        auto r = s.makeNext(ds);
        if (!r) {
            cout << -1;
        } else {
            for (auto& d : ds) cout << (int)d;
        }
        cout << endl;
    }
    
}
