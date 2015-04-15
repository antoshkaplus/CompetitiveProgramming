#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <locale>

using namespace std;


#define ST  stack
#define ST_i ST<int>
#define ST_i64 ST<int64_t>
#define ST_ii ST<pair<int, int>>


#define V  vector
#define V_i V<int>
#define V_s V<string>
#define V_b V<bool>
#define V_V_i V<V_i>
#define V_V_b V<V_b>
#define V_ii V<pair<int, int>>

#define P_ii pair<int, int>
#define P   pair

#define M   map
#define M_ii M<int, int>

#define UM unordered_map

#define S_i set<int>
#define S set

#define US unordered_set

#define ODD(n) ((n)%2 != 0) 
#define EVEN(n) ((n)%2 == 0)

struct NamingConvention {
    string toCamelCase(string variableName) {
        char diff = 'A' - 'a';
        string result;
        for (int i = 0; i < variableName.size(); ++i) {
            if (variableName[i] == '_') {
                variableName[i+1] += diff;
            } else {
                result += variableName[i];
            }
        }
        return result;
    }
};

struct NarrowPassage2Easy {
    int count(vector<int> size, int maxSizeSum) {
        
    
    }
};



