
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

string line;
int plus;
int eq;
int c_0;
int c_1;
int c_2;

int get_0() {
    return atoi(line.c_str());
}

int get_1() {
    return atoi(line.substr(::plus+1, eq-::plus).c_str());
}

int get_2() {
    return atoi(line.substr(eq+1).c_str());
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    // to the end of T
    getline(cin, line);
    for (int t = 0; t < T; ++t) {
        // blank line
        getline(cin, line);
        // real line
        getline(cin, line);
        ::plus = line.find_first_of('+');
        eq = line.find_first_of('=');
        auto mach = line.find("machula");
        if (mach < ::plus) {
            // first
            c_1 = get_1();
            c_2 = get_2();
            c_0 = c_2 - c_1;
        } else if (mach < eq) {
            // second
            c_0 = get_0();
            c_2 = get_2();
            c_1 = c_2 - c_0;
        } else {
            // res
            c_0 = get_0();
            c_1 = get_1();
            c_2 = c_0 + c_1;
        }
        cout << c_0 << " + " << c_1 << " = " << c_2 << endl;
    }
}
