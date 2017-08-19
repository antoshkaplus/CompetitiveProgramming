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
#include <cstring>

using namespace std;

using Count = int;
using Index = int;
using Int = int;

template<class T>
struct Grid {
    using value_type = T;
    
    typename std::vector<T>::const_iterator begin() const {
        return grid_.begin();
    }
    typename std::vector<T>::iterator begin() {
        return grid_.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return grid_.end();
    }
    typename std::vector<T>::iterator end() {
        return grid_.end();
    }
    
    Grid() : Grid(0, 0) {}
    Grid(Count row_count, Count col_count)
    :   row_count_(row_count), 
    col_count_(col_count), 
    grid_(row_count*col_count) {}
    
    
    void resize(Count row_count, Count col_count) {
        row_count_ = row_count;
        col_count_ = col_count;
        grid_.resize(row_count*col_count);
    }
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
    
    Count cell_count() const { return row_count()*col_count(); } 
    
    T& operator()(Int row, Int col) {
        return grid_[row*col_count_ + col];
    }
    
    const T& operator()(Int row, Int col) const {
        return grid_[row*col_count_ + col];
    }
    
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
};





class LCS { 
    using V_b = std::vector<bool>;
    using S = const std::string;
    
    Grid<int> dp;
    S *s_1_;
    S *s_2_;
    
    V_b *b_1_;
    V_b *b_2_;
    
    int sz_1;
    int sz_2;
    
public:
    LCS() {}
    
    std::tuple<V_b, V_b> compute(const std::string& s_1, const std::string& s_2){
        s_1_ = &s_1;
        s_2_ = &s_2;
        
        sz_1 = s_1.size();
        sz_2 = s_2.size();
        
        V_b b_1(sz_1, false);
        V_b b_2(sz_2, false);
        
        b_1_ = &b_1;
        b_2_ = &b_2; 
        
        dp.resize(sz_1+1, sz_2+1);
        
        CalcDP();
        Backtrack();
        
        return std::tuple<V_b, V_b>{std::move(b_1), std::move(b_2)};
    }   
    
private:
    
    void CalcDP() {
        auto& s_1 = *s_1_;
        auto& s_2 = *s_2_;
        
        for(int i = 0; i <= sz_1; i++) {
            dp(i, 0) = 0;
        }
        for(int j = 0; j <= sz_2; j++) {
            dp(0, j) = 0;
        }
        
        //  Calculate the matrix for LCS.
        for(int i = 1; i <= sz_1; i++){
            for(int j = 1; j <= sz_2; j++){
                if(s_1[i-1] == s_2[j-1]) {
                    dp(i, j) = dp(i-1, j-1) + 1;
                } else {
                    dp(i, j) = std::max(dp(i-1, j), dp(i, j-1));
                }
            }
        }
    }
    
    void Backtrack() {
        auto& s_1 = *s_1_;
        auto& s_2 = *s_2_;
        auto& b_1 = *b_1_; 
        auto& b_2 = *b_2_;
        
        int x = sz_1;
        int y = sz_2;
        while(true){
            if(x == 0 || y == 0)
                break;
            //  If two characters are equal, 
            //      move to diagonally opposite cell and mark the current position in b_1 and b_2 as true.
            //  else, move to the cell [x-1][y] or [x][y-1], whichever has the maximum value.
            if(s_1[x-1] == s_2[y-1]){
                b_1[x-1] = true;
                b_2[y-1] = true;
                --x;
                --y;
            } else if (dp(x-1, y) >= dp(x, y-1)) {
                --x;
            } else {
                --y;
            }
        }
    }
};






int main() {
    char s[105], t[105], res[210];
    while(scanf("%s", s) != EOF){
        scanf("%s", t);
        int sLength = strlen(s), tLength = strlen(t);
        //  Populate sArr and tArr.
        
        string s_1(s);
        string s_2(t);
        LCS ss;
        
        vector<bool> b_s, b_t;
        tie(b_s, b_t) = ss.compute(s_1, s_2);
        
        //  Merge two strings together.
        int i = 0, j = 0, idx = 0;
        while(i < sLength && j < tLength){
            int k = i, l = j;
            //  Add the characters from first string to resultant string which are not part of LCS.
            for(;k < sLength && !b_s[k];k++)
                res[idx++] = s[k];
            //  Add the characters from second string to resultant string which are not part of LCS.
            for(;l < tLength && !b_t[l];l++)
                res[idx++] = t[l];
            //  Add the characters to resultant string which are part of LCS.
            while(k < sLength && l < tLength && b_s[k] && b_t[l]){
                res[idx++] = s[k];
                k++;
                l++;
            }
            i = k;
            j = l;
        }
        //  Add remaining characters from the first string, if any.
        while(i < sLength)
            res[idx++] = s[i++];
        //  Add remaining characters from the second string, if any.
        while(j < tLength)
            res[idx++] = t[j++];
        res[idx] = 0;
        printf("%s\n", res);
    }
}