
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

typedef size_t Count;
typedef long long word_type;
typedef size_t Index;

struct bigint {
    
    bigint() {}
    bigint(const std::string& s) {
        Index s_i_begin = 0;
        while (std::isspace(s[s_i_begin])) {
            ++s_i_begin;
        }
        
        is_negative_ = false;
        if (s[s_i_begin] == '-') is_negative_ = true;
        if (s[s_i_begin] == '-' || s[s_i_begin] == '+') ++s_i_begin;
        
        Count n = 0;
        while (std::isdigit(s[s_i_begin + n])) {
            ++n;
        }
        init_words(s.c_str()+s_i_begin, n);
    }  
    
    void init_words(const char* s, Count n) {
        if (n == 0) {
            words_.resize(1);
            words_[0] = 0;
        }
        
        Count w_count = n/kWordDigitCount;
        Count rem = n%kWordDigitCount;
        char buf[kWordDigitCount+1]; // 0 character 
        #define assign(str, str_n, w_i) \
            std::memcpy(buf, str, str_n*sizeof(char)); \
            buf[str_n] = '\0'; \
            words_[w_i] = atol(buf); 
            
        if (rem > 0) { ;
            words_.resize(w_count+1);
            assign(s, rem, w_count);
        } else {
            words_.resize(w_count);
        }
        for (Int w_i = 0, s_i = (Int)n-kWordDigitCount; 
             w_i < w_count; ++w_i, s_i-=kWordDigitCount) {
            assign(s+s_i, kWordDigitCount, w_i);
        }
    }
    
    bool is_zero() const {
        return words_.size() == 1 && words_[0] == 0;
    }
    
    
private:

    static const size_t kWordDigitCount = 9;
    static const word_type kWordBase = 1e+9;
    
    bool is_negative_;
    std::vector<word_type> words_;
    // how many word should be empty on the right
    Count shift_;
    
    friend bigint operator*(const bigint& b_0, const bigint& b_1);
    friend bigint standard_multiplication(const bigint& b_0, const bigint& b_1);
    friend std::ostream& operator<<(std::ostream& output, const bigint& b);
};


bigint standard_multiplication(const bigint& b_0, const bigint& b_1) {
    bigint r;
    if (b_0.is_zero() || b_1.is_zero()) {
        r.words_.resize(1, 0);
        return r;
    }
    
    auto& w_0 = b_0.words_;
    auto& w_1 = b_1.words_;
    r.is_negative_ = b_0.is_negative_ ^ b_1.is_negative_; // should be bit operation 
                                                          // b_1 * b_0
                                                          // inner loop should be bigger?
    auto& w_r = r.words_; 
    w_r.resize(w_0.size() + w_1.size(), 0);
    for (auto i = 0; i < w_0.size(); ++i) {
        for (auto j = 0; j < w_1.size(); ++j) {
            w_r[i+j] += w_0[i]*w_1[j];
            w_r[i+j+1] += w_r[i+j]/bigint::kWordBase;
            w_r[i+j] %= bigint::kWordBase; 
        }
    }
    if (w_r.back() == 0) w_r.pop_back();
    return r;
}

//bigint karatsuba_multiplication(const bigint& b_0, const bigint& b_1) {
//    bigint r;
//}


bigint operator*(const bigint& b_0, const bigint& b_1) {
    return standard_multiplication(b_0, b_1);
}

std::ostream& operator<<(std::ostream& output, const bigint& b) {
    auto& w = b.words_;
    if (b.is_negative_ && w.back() != 0) output << '-';
    output << w.back();
    
    for (Int i = (Int)w.size()-2; i >= 0; --i) {
        output.width(bigint::kWordDigitCount);
        output.fill('0');
        output.setf(std::ios::right);
        
        output << w[i];
    }
    output.width(0);
    return output;
}   




int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        string s_0, s_1;
        cin >> s_0 >> s_1;
        bigint b_0(s_0);
        bigint b_1(s_1);
        cout << b_0*b_1 << endl;
    } 
}