

#include <stack>
#include <string>

using namespace std;

class DoubleLetter {
public:
string ableToSolve(string s) {
    stack<char> st;
    int i = 0;
    st.push(s[0]);
    
    while (++i != s.size()) {
        char ch = s[i];
        if (!st.empty() && ch == st.top()) {
            st.pop();
            continue;
        } 
        else {
            st.push(ch);
        }
    }
    return st.empty() ? "Possible" : "Impossible";
}

};