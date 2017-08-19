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



// here we describe line as 'y = a*x + b'
// look for convex hull trick algorithm for more info
// http://wcipeg.com/wiki/Convex_hull_trick
template<class V> 
class LowerEnvelope {
    
    struct L {
        V a, b;
        
        L() {}
        L(V a, V b) : a(a), b(b) {}
        
        V y(V x) {
            return a*x + b;
        }
    }; 
    
    vector<L> ls_;
    int ptr_ = 0; //Keeps track of the best line from previous query
    
    // we don't need middle if intersection between l_1,l_3 is on the left from l_1,l_2
    bool NeedPrelast() {
        auto& l_3 = *(ls_.end()-1);
        auto& l_2 = *(ls_.end()-2);
        auto& l_1 = *(ls_.end()-3);
        return (l_3.b - l_1.b)*(l_1.a - l_2.a) >= (l_2.b - l_1.b)*(l_1.a - l_3.a);
    }
    
public:
    
    // you have to add them in sorted order of 'a'
    // equal 'a' are not considered 
    void Add(V a, V b) {
        ls_.emplace_back(a, b);
        //If the penultimate is now made irrelevant between the antepenultimate
        //and the ultimate, remove it. Repeat as many times as necessary
        while (ls_.size() >= 3 && !NeedPrelast()) {
            ls_.erase(ls_.end()-2);
        }
    }
    
    V Query(V x) {
        //If we removed what was the best line for the previous query, then the
        //newly inserted line is now the best for that query
        if (ptr_ >= ls_.size()) {
            ptr_ = ls_.size()-1;
        }
        //Any better line must be to the right, since query values are
        //non-decreasing
        while (ptr_ < ls_.size()-1 && ls_[ptr_+1].y(x) < ls_[ptr_].y(x)) {
            
            ++ptr_;
        }
        return ls_[ptr_].y(x);
    }
    
};


struct R {
	int w, h;
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	
	vector<R> rs(N);
	for (auto& r : rs) {
		cin >> r.w >> r.h;
	}
	
	// inc height, dec width
	sort(rs.begin(), rs.end(), [](const R& r_1, const R& r_2) {
		return r_1.h < r_2.h || (r_1.h == r_2.h && r_1.w > r_2.w);	
	});
	
	// exclude rectangle we don't need 
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j >= 0 && rs[i].w >= rs[j].w) {
			--j;
		}
		++j;
		rs[j] = rs[i];
	}
	// now we can shrink the array
	N = j + 1;
    rs.resize(N);
	
    
	// dynamic prog
//	vector<int> cost(N, numeric_limits<int>::max());
//	for (int i = 0; i < N; ++i) {
//		for (int j = 0; j < i-1; ++j) {
//			cost[i] = min(cost[i], cost[j] + rs[i].h*rs[j+1].w);
//		}
//	}
    
    LowerEnvelope<int64_t> lowerEnv;
    // first line is just must have
    lowerEnv.Add(rs[0].w, 0);
    
    int64_t cost;
    for (int i = 0; i < N-1; ++i) {
        cost = lowerEnv.Query(rs[i].h);
        lowerEnv.Add(rs[i+1].w, cost);
    } 
    cost = lowerEnv.Query(rs[N-1].h);
	cout << cost;
}














