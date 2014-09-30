#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct HappyLetterDiv2 {
    char getHappyLetter(string str) {
        const int n = 'z'-'a' + 1;
        int count[n];
        fill_n(count, n, 0);
        for (int i = 0; i < str.size(); ++i) {
            ++count[str[i]-'a'];
        }
        int s;
        int m = 0;
        char ch = 0;
        for (int i = 0; i < n; ++i) {
            if (count[i] > m) {
                s += m;
                m = count[i];
                ch = i + 'a';
            } else {
                s += count[i];
            }
        }
        if (m > s) {
            return ch;
        } else {
            return '.';
        }
    }
};