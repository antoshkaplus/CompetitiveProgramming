
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

typedef int Index;
typedef int Count;

struct disjoint_set {
    disjoint_set() {}
    disjoint_set(Count element_count) {
        init(element_count);
    }
    
    void init(Count element_count) {
        element_count_ = element_count;
        set_count_ = element_count;
        data_.resize(element_count);
        size_.resize(element_count);
        reset();
    }
    
    void reset() {
        for (int i = 0; i < data_.size(); ++i) {
            data_[i]  = i;
        }    
        fill(size_.begin(), size_.end(), 1);
    }
    
    void unite(Index i_0, Index i_1) {
        --set_count_;
        Index
        r_0 = root(i_0),
        r_1 = root(i_1);
        // will join r_0 to r_1, so r_1 height should be bigger
        if (size_[r_0] > size_[r_1]) {
            std::swap(r_0, r_1);
        }
        data_[r_0] = r_1;
        size_[r_1] += size_[r_0];
        
    }
    
    bool is_separate(Index i_0, Index i_1) {
        return root(i_0) != root(i_1);
    }
    
    Index root(Index i) {
        while (i != data_[i]) {
            i = data_[i] = data_[data_[i]];
        }
        return i;
    }
    
    size_t size() {
        return element_count_;
    }
    
    Count set_count() {
        return set_count_;
    }
    
    Count element_count_;
    Count set_count_;
    std::vector<Index> data_;
    std::vector<size_t> size_;
};


struct Item {
    Item() {}
    Item(int i_0, int i_1, int c) : i_0(i_0), i_1(i_1), c(c) {}
    int i_0;
    int i_1;
    int c;
    // need min queue
    bool operator<(const Item& item) const {
        return c > item.c;
    }
};

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n;
        cin >> n;
        disjoint_set s(n);
        priority_queue<Item> q;
        string str;
        for (int i = 0; i < n; ++i) {
            cin >> str;
            int n_count;
            cin >> n_count;
            Item m;
            m.i_0 = i;
            for (int j = 0; j < n_count; ++j) {
                cin >> m.i_1 >> m.c;
                --m.i_1;
                if (i < m.i_1) continue;
                q.push(m); 
            }
        }
        unsigned int r = 0;
        while (!q.empty()) {
            const Item& top = q.top();
            if (s.is_separate(top.i_0, top.i_1)) {
                s.unite(top.i_0, top.i_1);
                r += top.c;
            }
            q.pop();
        }
        
        cout << r << endl;
    }
}
















