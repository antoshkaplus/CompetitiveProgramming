
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

using namespace std;

bool isCapital(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

bool isRaw(char ch) {
    return ch >= 'a' && ch <= 'z';
}

char lower(char ch) {
    return ch - ('A' - 'a');
}

char upper(char ch) {
    return ch + ('A' - 'a');
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    while (!cin.eof()) {
        string str;
        getline(cin, str);
        auto index = str.find('_');
        auto hasUnderscore = string::npos != index;
        auto hasCapital = false;
        for (auto& ch : str) {
            if (isCapital(ch)) {
                hasCapital = true;
                break;
            }
        }
        if (hasCapital && hasUnderscore) {
            cout << "Error!" << endl;
            continue;
        }
        if (!isRaw(str.front())) {
            cout << "Error!" << endl;
            continue;
        }
        string res;
        bool prevUnderscore = false;
        for (auto ch : str) {
            if (ch == '_') {
                if (prevUnderscore) {
                    break;
                }
                prevUnderscore = true;
                continue;
            }
            if (isCapital(ch)) {
                res += '_';
                res += lower(ch);
                continue;
            }
            if (prevUnderscore) {
                prevUnderscore = false;
                res += ::upper(ch);
                continue;
            }
            res += ch;
        }
        if (prevUnderscore) {
            cout << "Error!" << endl;
            continue;
        }
        cout << res << endl;
    }
    
}





