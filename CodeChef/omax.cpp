
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
#include <stack>
#include <deque>
#include <assert.h>

using namespace std;

const int kMaxMN = 77;
bool *VALUE_FOUND[kMaxMN][kMaxMN][kMaxMN];
bool *MIN_HOLE_FOUND[kMaxMN][kMaxMN][kMaxMN];
bool *ANSWER_FOUND[kMaxMN][kMaxMN][kMaxMN];
int *VALUE[kMaxMN][kMaxMN][kMaxMN];
int *MIN_HOLE_FOUND[kMaxMN][kMaxMN][kMaxMN];


int value(int r_0, int c_0, int r_1, int c_1) {
    if (VALUE_FOUND[r_0][c_0][r_1][c_1]) {
        return VALUE[r_0][c_0][r_1][c_1];
    } else {
        if (r_1 - r_0 == 0) {
            return value(r_0, c_0, r_1, c_1-1)
                + value(r_0, c_1, r_1, c_1);
        } else {
            return value(r_0, c_0, r_1-1, c_1) 
                + value(r_1, c_0, r_1, c_1);
        }
    }
}


int min_hole(int r_0, int c_0, int r_1, int c_1) {
    if (MIN_HOLE_FOUND[r_0][c_0][r_1][c_1]) {
        return MIN_HOLE[r_0][c_0][r_1][c_1];
    } else {
        int mh[5];
        int mh_sz = 0;
        mh[mh_sz++] = value(r_0, c_0, r_1, c_1);
        if (r_1-r_0 > 0) {
            mh[mh_sz++] = min_hole(r_0+1, c_0, r_1, c_1);
            mh[mh_sz++] = min_hole(r_0, c_0, r_1-1, c_1);
        }
        if (c_1-c_0 > 0) {
            mh[mh_sz++] = min_hole(r_0, c_0+1, r_1, c_1);
            mh[mh_sz++] = min_hole(r_0, c_0, r_1, c_1-1);
        }
        return *min_element(mh, mh+mh_sz);
    }
}

int answer(int r_0, int c_0, int r_1, int c_1) {
    int as[5];
    int as_sz = 0;
    as[as_sz++] = value(r_0, c_0, r_1, c_1) - min_hole(r_0+1, c_0+1, r_1-1, c_1-1);
    if (r_1 - r_0 > 1) {
        as[as_sz++] = answer(r_0+1, c_0, r_1, c_1);
        as[as_sz++] = answer(r_0, c_0, r_1-1, c_1);
    }
    if (c_1 - c_0 > 1) {
        as[as_sz++] = answer(r_0, c_0+1, r_1, c_1);
        as[as_sz++] = answer(r_0, c_0, r_1, c_1-1);
    } 
    return *max_element()
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int M, N;
    
    
    bool *_found = new bool[kMaxMN*kMaxMN*kMaxMN*kMaxMN];
    bool found[] = &&&_found;
    int *_value = new int[kMaxMN*kMaxMN*kMaxMN*kMaxMN];
    int ****value = &&&_value;
    
    while (true) {
        cin >> M >> N;
        if (M == 0 && N == 0) break;
        
        fill_n(_found, M*N*M*N, false);
        
    }    
    
}













