#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;




// stack uses only open or X (open inside)
struct BracketExpressions {
    
    string exp;
    
    bool isOpen(char ch) {
        return ch == '(' || ch == '[' || ch == '{';
    }
    
    char openOpposite(char ch) {
        switch(ch) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        default: assert(false);
        }
    }
    
    char closeOpposite(char ch) {
        switch(ch) {
            case ')': return '(';
            case ']': return '[';
            case '}': return '{';
            default: assert(false);
        }
    }
    
    
    // i - next element to research
    bool go(stack<char>& st, int i) {
        if (i == exp.size()) {
            return st.empty(); 
        }
        
        bool res = false;
        if (exp[i] == 'X') {
            if (!st.empty()) {
                auto st_0 = st;
                st_0.pop();
                res = go(st_0, i+1);
            }
            if (!res) {
                st.push('X');
                res = go(st, i+1);
            }
        } else if (isOpen(exp[i])) {
            st.push(exp[i]);
            res = go(st, i+1);
        } else if (!st.empty() && 
                   (st.top() == 'X' || 
                    st.top() == closeOpposite(exp[i]))) {
            st.pop();
            res = go(st, i+1);
        }  
        return res;
    }
    
    
    string ifPossible(string exp) {
        this->exp = exp;
        stack<char> st;
        return go(st, 0) ? "possible" : "impossible";
    }
};






