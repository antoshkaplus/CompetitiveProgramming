#include <queue>
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

uint64_t MOD = 1000000007;

template<class T>
class Median {
public:
    void add(T n) {
        if (p_min_snd.size() == p_max_fst.size()) {
            // we should increase size of p_min_snd
            if (!p_max_fst.empty() && n <= p_max_fst.top()) {
                p_max_fst.push(n);
                p_min_snd.push(p_max_fst.top());
                p_max_fst.pop();
            } else {
                p_min_snd.push(n);
            }
        } else {
            // invariant is there
            // we should make equal now
            if (n <= p_min_snd.top()) {
                p_max_fst.push(n);
            } else {
                p_min_snd.push(n);
                p_max_fst.push(p_min_snd.top());
                p_min_snd.pop();
            }
        }
        
    }
    
    
    const T& get() const {
        if (p_min_snd.size() == p_max_fst.size()) {
            return p_max_fst.top();
        } else {
            return p_min_snd.top();
            
        }
    }
    
    // or we could not return anything at all
    T pop() {
        T r;
        if (p_min_snd.size() == p_max_fst.size()) {
            r = p_max_fst.top();
            p_max_fst.pop();
        } else {
            r = p_min_snd.top();
            p_min_snd.pop();
        }
        return r;
    }
private:
    priority_queue<T, std::vector<T>, std::less<T>> p_max_fst;
    priority_queue<T, std::vector<T>, std::greater<T>> p_min_snd;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        uint64_t a, b, c, n;
        cin >> a >> b >> c >> n;
        
        uint64_t f_sum = 1;
        Median<uint64_t> median;
        
        median.add(1);
        
        for (auto i = 2; i <= n; ++i) {
            auto f = (a*median.get() + b*i + c) % MOD;
            median.add(f);
            f_sum += f; 
        } 
        cout << f_sum << endl;
    }
}
