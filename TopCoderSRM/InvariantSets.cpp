#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct InvariantSets {
    long long countSets(vector<int> f) {
        vector<int> parent(f.size(), -1);
        vector<int> order(f.size());
        for (int i = 0; i < f.size(); ++i) {
            if (parent[i] != -1) {
                continue;
            }
            int j = i;
            int k = 0;
            vector<int> elem;
            while (parent[j] == -1) {
                parent[j] = i;
                order[j] = --k;
                elem.push_back(j);
                j = f[j];
            }
            
            if (parent[j] == i) {
                int r = -order[j] - 1;
                for (int q = 0; q < r; ++q) {
                    order[elem[q]] = r-q;
                    parent[elem[q]] = q == r-1 ? j : elem[q+1];
                }
                for (int q = r; q < elem.size(); ++q) {
                    order[elem[q]] = 0;
                    parent[elem[q]] = j;
                }
            } else {
                for (int q = 0; q < elem.size(); ++q) {
                    order[elem[q]] = elem.size() - q + order[j];
                    if (q != elem.size()-1) {
                        parent[elem[q]] = elem[q+1];    
                    } else {
                        if (order[j] == 0) {
                            parent[elem[q]] = parent[j];
                        } else {
                            parent[elem[q]] = j;
                        }
                    }
                }
            }
        }
        
        
        vector<int> inds;
        for (int i = 0; i < f.size(); ++i) {
            if (parent[i] == i || order[i] != 0) inds.push_back(i);
        }
        // biggest order first
        sort(inds.begin(), inds.end(), [&](int i_0, int i_1) {
            return order[i_0] > order[i_1];
        });
        
        for (int i = 0; i < f.size(); ++i) {
            cout << parent[i] << "," << order[i] << "  ";
        }
        cout << endl;
        // last element is special
        vector<vector<long long>> ch_counts(f.size()+1);
        for (int i : inds) {
            if (order[i] == 0) parent[i] = f.size();
        }
        for (int i : inds) {
            if (ch_counts[i].size() == 0) {
                ch_counts[parent[i]].push_back(2);
            } else {
                long long p = 1;
                for (long long ch : ch_counts[i]) {
                    p *= ch;
                }
                ch_counts[parent[i]].push_back(p + 1);
            }
            cout << i << "," << ch_counts[parent[i]].back() << "   ";
        }
        long long p = 1;
        for (long long ch : ch_counts[ch_counts.size()-1]) {
            p *= ch;
        }
        return p;
        
    }
};