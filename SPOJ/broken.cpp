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
#include <functional>
#include <bitset>

using namespace std;


using Count = int;

template<class Key, class Value>
using Map = std::map<Key, Value>;


template <class T, template<class, class> class M = Map>
class CountMap : public M<T, Count> {
public:
    void decrease(const T& t) { decrease(t, 1); }
    
    void decrease(const T& t, Count val) {
        auto it = this->find(t);
        if ((it->second-=val) == 0) {
            this->erase(it);
        }
    }
    
    void increase(const T& t) { increase(t, 1); }
    
    void increase(const T& t, Count val) {
        this->emplace(t, 0).first->second+=val;
    }
    
    std::set<T> keys() const {
        std::set<T> r;
        for (auto p : *this) {
            r.insert(p.first);
        }
        return r;
    }
    
    size_t get(const T& t) const {
        auto it = this->find(t);
        return it == this->end() ? 0 : it->second;
    }
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    for (;;) {
        int m;
        cin >> m;
        if (m == 0) break;
        string text;
        // read new line char
        getline(cin, text);
        getline(cin, text);
        CountMap<char> cm;
        auto i_start = 0;
        auto max_substr = 0;
        for (auto i = 0; i < text.size(); ++i) {
            cm.increase(text[i]);
            while (cm.size() > m) {
                cm.decrease(text[i_start]);
                i_start++;
            }
            if (cm.size() <= m) {
                max_substr = max(i - i_start + 1, max_substr);
            }
        }
        cout << max_substr << endl;
    }
    
}






