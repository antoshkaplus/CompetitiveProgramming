
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

const int BOUND = 101;

int hash(const string& str) {
    int s = 0;
    for (int i = 0; i < str.size(); ++i) {
        s += (i+1)*(str[i]);
    }
    s *= 19;
    return s;
}

string arr[BOUND];
int step[20];

void insert(const string& str) {
    int key = hash(str);
    int first_free = -1;
    for (int i = 0; i < 20; ++i) {
        int k = (key + step[i])%BOUND;
        if (arr[k] == str) {
            first_free = -1;
            break;
        }
        if (first_free < 0 && arr[k] == "") {
            first_free = k;
        } 
    }
    if (first_free >= 0) arr[first_free] = str; 
}

void remove(const string& str) {
    int key = hash(str);
    for (int i = 0; i < 20; ++i) {
        int k = (key + step[i])%BOUND;
        if (arr[k] == str) {
            arr[k] = "";
            break;
        } 
    }
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 0; i < 20; ++i) {
        step[i] = i*i + 23*i; 
    }
    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < BOUND; ++i) {
            arr[i] = "";
        }
        int n;
        string s;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            if (s[0] == 'A') {
                insert(s.substr(4));
            } else {
                remove(s.substr(4));
            }
        }
        int size = 0;
        for (int i = 0; i < BOUND; ++i) {
            if (arr[i] != "") {
                ++size; 
            }
        }  
        cout << size << endl;
        for (int i = 0; i < BOUND; ++i) {
            if (arr[i] != "") {
                cout << i << ":" << arr[i] << endl; 
            } 
        }
        cout << endl;
    }
}












