
#include <memory>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

using Count = int;
using Index = int;


template <class T>
class CounterSkipList {
    
public:
    
    
    struct HeightGen {
        HeightGen() {}
        
        HeightGen(int max, float prob) {
            std::vector<double> probs(max);
            for (auto& p : probs) {
                p = prob;
                prob *= 0.5;
            }
            distr = std::discrete_distribution<int>(probs.begin(), probs.end());
        }
        ~HeightGen() {}
        
        int operator()() {
            return distr(rng) + 1;
        }
        
    private:
        std::default_random_engine rng;
        std::discrete_distribution<int> distr;
    };
    
    
    struct Node
    {
    // number of those is equal to height
    std::vector<std::shared_ptr<Node>> next;
    std::vector<Count> numAfterPrev;
    T value;
    
    Node() {}
    
    Node(int h, const T& t) 
    : next(h), numAfterPrev(h, 1), value(t) {}
    
    Node(int h) 
    : next(h), numAfterPrev(h, 1) {}
    
    int height() const {
        return next.size();
    }
    };    
    
    
    CounterSkipList(int maxNumElems) : count(0), curHeight(0), heightGen(std::log2(maxNumElems), 0.5) {
        int maxHeight = std::log2(maxNumElems);
        
        head = std::make_shared<Node>(maxHeight);
        tail = std::make_shared<Node>(maxHeight);
        
        for (Index i = 0; i < maxHeight; ++i) {
            head->next[i] = tail;
        }
    }
    
    ~CounterSkipList() {
        auto cur = head;
        // tail items are empty
        while (cur != tail) {
            auto next = cur->next[0];
            for (auto& sh : cur->next) {
                sh.reset();
            }
            cur = next;
        }
        
    }
    
    void insert(std::shared_ptr<Node> prev, std::shared_ptr<Node> newNode, int pos, int i) {
        newNode->next[i] = prev->next[i];
        prev->next[i] = newNode;
        newNode->numAfterPrev[i] = pos;
        newNode->next[i]->numAfterPrev[i] -= pos-1;
    }
    
    void remove(std::shared_ptr<Node> prev, std::shared_ptr<Node> cur, int i) {
        cur->next[i]->numAfterPrev[i] += cur->numAfterPrev[i] - 1;
        prev->next[i] = cur->next[i];
    }
    
    void insertAt(Index pos, const T& val) {
        pos += 1;
        
        auto height = heightGen();
        std::shared_ptr<Node> newNode = std::make_shared<Node>(height, val);
        
        if (height > curHeight) {
            for (auto i = curHeight; i < height; ++i) {
                tail->numAfterPrev[i] += count;
            }
            curHeight = height;
        }
        
        auto cur = head;
        for (auto i = curHeight-1; i >= 0; --i) {
            while (cur->next[i] != tail && cur->next[i]->numAfterPrev[i] < pos) {
                cur = cur->next[i];
                pos -= cur->numAfterPrev[i];
            }
            if (i < height) {
                insert(cur, newNode, pos, i);
            } else {
                ++cur->next[i]->numAfterPrev[i];
            }
        }
        ++count;
    }
    
    void removeAt(Index pos) {
        pos += 1;
        
        auto cur = head;
        auto prev = head;
        for (auto i = curHeight-1; i >= 0; --i) {
            while (pos > 0) {
                prev = cur;
                cur = cur->next[i];
                pos -= cur->numAfterPrev[i];
            }
            
            if (pos == 0) {
                remove(prev, cur, i);
            } 
            pos += cur->numAfterPrev[i];
            // if cur is not deleted we have to reduce num
            --cur->numAfterPrev[i];
            cur = prev; 
        }
        --count;
    }
    
    const T& operator[](Index pos) const {
        pos += 1;
        
        auto cur = head;
        for (auto i = curHeight-1; i >= 0; --i) {
            while (cur->next[i] != tail && cur->next[i]->numAfterPrev[i] <= pos) {
                cur = cur->next[i];
                pos -= cur->numAfterPrev[i];
            }
            if (pos == 0) {
                return cur->value;
            } 
        }
        throw std::runtime_error("out of range");
    }
    
    int count;
    int curHeight;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    HeightGen heightGen;
};

int N_MAX = 100000;
int Q_MAX = 100000;

int main() {
    std::ios_base::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    CounterSkipList<int> list(N_MAX + Q_MAX);
    for (auto i = 0; i < N; ++i) {
        int A;
        cin >> A;
        list.insertAt(i, A);
    }
    for (auto i = 0; i < Q; ++i) {
        int a, k, x;
        cin >> a >> k; --k;
        switch(a) {
            case 1:
                cin >> x;
                list.insertAt(k, x);
                break;
            case 2:
                list.removeAt(k);
                break;
            case 3:
                cout << list[k] << endl;
                break;
        }
    }
    
    
}
