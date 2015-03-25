

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


typedef int Int;
typedef int Index;


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
    Int x, y;
};
bool operator==(const Point& p_0, const Point& p_1){
    return p_0.x == p_1.x && p_0.y == p_1.y;
}

static int cross_product(const Point& p_0, const Point& p_1, const Point& p_2) {
    return (p_1.x - p_0.x)*(p_2.y - p_0.y) - (p_1.y - p_0.y)*(p_2.x - p_0.x);
}

struct Comp {
    Comp(const vector<Point>& ps) : ps(ps) {}
    bool operator()(Index i_0, Index i_1) const {
        return ps[i_0].x < ps[i_1].x || (ps[i_0].x == ps[i_1].x && ps[i_0].y < ps[i_1].y);
    }	
    const vector<Point>& ps; 
};

std::vector<Index> convex_hull(const std::vector<Point>& ps, bool is_clockwise) {
    std::vector<Index> U, L;
    std::vector<Index> PP(ps.size());
    for (int i =0 ; i < ps.size(); ++i) {
        PP[i] = i;
    }
    std::sort(PP.begin(), PP.end(),Comp(ps));
    vector<Index> P;	
    P.reserve(ps.size());
    for (int i = 0; i < ps.size(); ++i) {
        if (i > 0 && ps[PP[i-1]] == ps[PP[i]]) continue;
        P.push_back(PP[i]);
    }
    if (P.size() == 1) return P;
    // lower hull
    for (int i = 0; i < P.size(); ++i) {
        while (L.size() >= 2 && cross_product(ps[L[L.size()-2]], ps[L[L.size()-1]], ps[P[i]]) <= 0) {
            L.pop_back();
        }
        L.push_back(P[i]);
    }
    // upper hull
    for (int i = (Int)P.size()-1; i >= 0; --i) {
        while (U.size() >= 2 && cross_product(ps[U[U.size()-2]], ps[U[U.size()-1]], ps[P[i]]) <= 0) {
            U.pop_back();
        }
        U.push_back(P[i]);
    }
    P.assign(L.begin(), L.end()-1);
    P.insert(P.end(), U.begin(), U.end()-1);
    if (is_clockwise) {
        std::reverse(P.begin(), P.end());
    }
    return P;
}

double ddistance(const Point& p_0, const Point& p_1) {
    return sqrt(pow(p_0.x - p_1.x, 2) + pow(p_0.y - p_1.y, 2));
}

int main(int argc, char **argv) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n;
        cin >> n;
        vector<Point> ss(n);
        for (int i = 0; i < n; ++i) {
            cin >> ss[i].x >> ss[i].y;
        }
        vector<Index> res = convex_hull(ss, false);
        double length = 0;
        for (int i = 1; i < res.size(); ++i) {
            length += ddistance(ss[res[i-1]], ss[res[i]]);
        }
        if (res.size() > 1) length += ddistance(ss[res[0]], ss[res[res.size()-1]]);
        printf("%.2lf\n", length);
        int i_min = 0;
        for (int i = 1; i < res.size(); ++i) {
            if (ss[res[i_min]].y > ss[res[i]].y || (ss[res[i_min]].y == ss[res[i]].y && ss[res[i_min]].x > ss[res[i]].x)) {
                i_min = i;
            }
        }
        for (int i = 0; i < res.size(); ++i) {
            cout << res[(i+i_min)%res.size()]+1 << " ";
        }
        cout << endl;
        cout << endl;
    } 
}