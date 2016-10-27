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
class UpperEnvelope {
    
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
        return (l_3.b - l_1.b)*(l_1.a - l_2.a) <= (l_2.b - l_1.b)*(l_1.a - l_3.a);
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
        while (ptr_ < ls_.size()-1 && ls_[ptr_+1].y(x) > ls_[ptr_].y(x)) {
            
            ++ptr_;
        }
        return ls_[ptr_].y(x);
    }
    
};

struct Test {
	vector<int64_t> xs;
	int64_t a, b, c;
}

int64_t BruteForce(const Test& t) {
	int N = t.xs.size();
	
	vector<int64_t> sum(N, 0);
	sum[0] = t.xs[0];
	for (int i = 1; i < N; ++i) {
		sum[i] += sum[i-1] + t.xs[i];
	}
	
	adjust = [](int k) {
		// don't k-1 because k can equal 0
		s = sum.back() - sum[k] + xs[k];
		return t.a * s * s + t.b * s + t.c;
	};
	vector<int> dp(N+1, numeric_limits<int>::min());
    dp[0] = 0
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j <= i-1; ++j) {
			dp[i] = max(dp[i], dp[j] + adjust(j));
		}
    }
	return dp.back();
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        int64_t a, b, c;
        cin >> a >> b >> c;
        
        vector<int64_t> xs(N);
        for (auto& x : xs) {
            cin >> x;
        }
        
        //  dynamic prog
        //  sum(i,j) = x[i] + x[i+1] + ... + x[j]
        //  adjust(k) = a*sum(k,N)^2 + b*sum(k,N) + c
        //	vector<int> dp(N+1, numeric_limits<int>::min());
        //  dp[0] = 0
        //  for (int i = 1; i <= N; ++i) {
        //		for (int j = 0; j <= i-1; ++j) {
        //			dp[i] = max(dp[i], dp[j] + adjust(j+1));
        //		}
        //	}
        
        vector<int64_t> sum(N, 0);
        sum[0] = xs[0];
        for (int i = 1; i < N; ++i) {
            sum[i] += sum[i-1] + xs[i];
        }
        
        UpperEnvelope<int64_t> upperEnv;
        // first line is just must have
        int64_t r = a * sum[0] * sum[0] + b * sum[0] + c;
        upperEnv.Add(-2 * a * sum[0] , r + a * sum[0] * sum[0] - b * sum[0]);
        
        for (int i = 1; i < N; ++i) {
            r = a * sum[i] * sum[i] + b * sum[i] + c;
            r = max(r, b * sum[i] + a * sum[i] * sum[i] + c + upperEnv.Query(sum[i]));
            upperEnv.Add(-2 * a * sum[i] , r + a * sum[i] * sum[i] - b * sum[i]);
        } 
        cout << r << endl;
    }
}
