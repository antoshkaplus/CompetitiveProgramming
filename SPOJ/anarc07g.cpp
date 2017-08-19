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

using Index = int;

template<class T>
using AdjacencyList = std::vector<std::vector<T>>;

using NodeAdjacencyList = AdjacencyList<Index>;


template<class Index>
AdjacencyList<Index> Reverse(const AdjacencyList<Index>& adj) {
    int V = adj.size();
    AdjacencyList<Index> adj_new(V);
    for (int i = 0; i < V; ++i) {
        for (int j : adj[i]) {
            adj_new[j].push_back(i);
        }
    }
    return adj_new;
}

inline std::vector<std::string> Split(std::string str, char delim) {
    std::vector<std::string> r;
    Index s_i = 0; // starting index for sustr
    for (Index i = 0; i < str.size(); ++i) {
        if (str[i] == delim) {
            r.push_back(str.substr(s_i, i-s_i));
            s_i = i+1;
        }
    }
    r.push_back(str.substr(s_i));
    return r;
}

template<class T>
void SwapBackPop(std::vector<T>& v, Index i) {
    swap(v[i], v.back());
    v.pop_back();
}

using AdjList = NodeAdjacencyList;


// prices of both are somewhere
struct OptBuy {
    int s{0};
    int f{0};
    
    bool Empty() const {
        return s == 0 && f == 0;
    }
    
    int Count() const {
        return s + f;
    }
    
    OptBuy& operator+=(const OptBuy& buy) {
        s += buy.s;
        f += buy.f;
        return *this;
    }
};

struct Price {
    int s{0};
    int f{0};
    
    bool Empty() const {
        return s == 0 && f == 0;
    }
};

int ComputePrice(const OptBuy& buy, const Price& p) {
    return buy.s * p.s + buy.f * p.f;
}

class OptBuySolver {
public:    
    OptBuy Solve(const AdjList& adj_list, const Price& price) {
        adj_list_ = &adj_list;
        price_ = price;
        
        auto sz = adj_list.size();
        maybe_uncovered_ = covered_ = vector<OptBuy>(sz);
        
        OptBuy opt_buy;
        for (auto r : FindRoots()) {
            opt_buy += ComputeCovered(r);
        }
        return opt_buy;
    }
    
private:
    
    vector<int> FindRoots() {
        vector<int> roots;
        auto& al = *adj_list_;
        auto rev_al = Reverse(al);
        for (auto i = 0; i < rev_al.size(); ++i) {
            if (rev_al[i].empty()) {
                roots.push_back(i);   
            }
        }
        return roots;
    }
    
    OptBuy ComputeCovered(Index r) {
        auto& al = *adj_list_;
        
        if (al[r].empty()) {
            return {1,0};  
        }         
        
        if (!covered_[r].Empty()) {
            return covered_[r];
        }
        
        // by single
        OptBuy s_1;
        s_1.s = 1;
        for (auto i : al[r]) {
            s_1 += ComputeCovered(i);
        }
        // by family
        OptBuy s_2;
        s_2.f = 1;
        for (auto i : al[r]) {
            s_2 += ComputeMaybeUncovered(i);
        }
        return covered_[r] = Min(s_1, s_2);
    }
    
    OptBuy ComputeMaybeUncovered(Index r) {
        auto& al = *adj_list_;
        
        if (al[r].empty()) {
            return {0,0};   
        }
        
        if (!maybe_uncovered_[r].Empty()) {
            return maybe_uncovered_[r];
        }
           
        OptBuy s;
        for (auto i : al[r]) {
            s += ComputeCovered(i);
        }
        return maybe_uncovered_[r] = Min(ComputeCovered(r), s);
    }
    
    OptBuy Min(const OptBuy& s_1, const OptBuy& s_2) const {
        int p_1 = ComputePrice(s_1, price_);
        int p_2 = ComputePrice(s_2, price_);
        if (p_1 < p_2) return s_1;
        if (p_1 > p_2) return s_2;
        return s_1.Count() < s_2.Count() ? s_1 : s_2;
    }
    
    
    Price price_;
    vector<OptBuy> covered_;
    vector<OptBuy> maybe_uncovered_;
    const AdjList* adj_list_; 
};

void solve(istream& cin, ostream& cout) {
    string str;
    // convert name to Id
    map<string, int> nameId;
    int newId = 0;
    AdjList adj_list;
    Price price;
    
    int test_case;
    bool first = true;
    for (;;) {
        getline(cin, str);
        if (str.back() == '\r') str.pop_back();
        
        if (isdigit(str[0])) {
            
            if (first) {
                first = false;
                test_case = 1;
                
            } else {
                
                OptBuySolver solver;
                OptBuy buy = solver.Solve(adj_list, price);
                cout << test_case << ". " << buy.s << " " << buy.f << " " 
                    << ComputePrice(buy, price) << endl;
                
                nameId.clear();
                newId = 0;
                adj_list.clear();
                
                ++test_case;
            }
            
            auto ps = Split(str, ' ');
            price.s = std::stoi(ps[0]);
            price.f = std::stoi(ps[1]);
            
            if (price.s > price.f) throw runtime_error("lolz");
            
            if (price.Empty()) break;
            
        } else {
            
            // its list of names
            auto names = Split(str, ' ');
            for (auto& n : names) {
                if (nameId.count(n) == 0) {
                    nameId[n] = newId++;
                    adj_list.resize(adj_list.size()+1);
                }
            }
            int parent = nameId[names[0]];
            SwapBackPop(names, 0);
            for (auto& n : names) {
                adj_list[parent].push_back(nameId[n]);
            }
        }
    }
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    ifstream cin("../in.txt");
    solve(cin, cout);
}
