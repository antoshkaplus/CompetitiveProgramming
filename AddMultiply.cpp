#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct AddMultiply {

    vector<int> makeExpression(int y) {
        int x_0, x_1 = 2, x_2;
        for (x_0 = -1000; x_0 <= 1000; ++x_0) {
            x_2 = y - x_0 * x_1;
            if (x_2 < -1000 || x_2 > 1000) continue;
            break;
        }
        return {x_0, x_1, x_2};
    }
};