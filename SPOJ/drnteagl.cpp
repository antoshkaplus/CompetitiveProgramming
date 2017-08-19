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
#include <array>
#include <fstream>


using namespace std;

using Int = int64_t;
using Index = int64_t;


struct Point {
    Point() {}
    Point(Int x, Int y) : x(x), y(y) {}
    void set(Int x, Int y) {
        this->x = x;
        this->y = y;
    }
    void swap() {
        std::swap(x, y);
    }
    
    int distance(const Point& p) const {
        return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
    }
    
    Int x, y;
};


template <class ForwardIterator, class P>
ForwardIterator FarthestPoint(ForwardIterator firstIndex,
                              ForwardIterator lastIndex,
                              const P& p) {
    return std::max_element(firstIndex, lastIndex, [&](const Point& p_1, const Point& p_2) {
        return p_1.distance(p) < p_2.distance(p);
    });
}



int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<Point> ps(N); 
        for (auto& p : ps) {
            cin >> p.x >> p.y;
        }
        int i = FarthestPoint(ps.begin(), ps.end(), Point{0, 0}) - ps.begin();
        cout << "Case " << (t+1) << ": " << (i+1) << endl << endl;
    }
}











