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

using Int = int;
using Index = int;

template<class P>
double CrossProduct(const P& p_0, const P& p_1, const P& p_2) {
    return (p_1.x - p_0.x)*(p_2.y - p_0.y) - (p_1.y - p_0.y)*(p_2.x - p_0.x);
}

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

// always counter clockwise
// to make clockwise just reverse
template<class P> // should have x and y inside
std::vector<Index> ConvexHull(const std::vector<P>& ps) {
    std::vector<Index> inds;
    int n = (int)ps.size();
    std::vector<Index> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    // Sort points lexicographically
    sort(order.begin(), order.end(), 
         [&ps](int i1, int i2){ return ps[i1].x < ps[i2].x || 
             (ps[i1].x == ps[i2].x && ps[i1].y < ps[i2].y); });
    inds.resize(2*n);
    int k = 0;
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && CrossProduct(ps[inds[k-1]], ps[inds[k-2]], ps[order[i]]) <= 0) k--;
        inds[k++] = order[i];
    }
    // Build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && CrossProduct(ps[inds[k-1]], ps[inds[k-2]], ps[order[i]]) <= 0) k--;
        inds[k++] = order[i];
    }
    inds.resize(k-1);
    return inds;
}

bool IsInConvexPolygon(const std::vector<Point>& ps, Point p) {
    
    auto sign_1 = 0;
    auto p_1 = ps.back();
    for (auto i = 0; i < ps.size(); i++)
        {
        auto p_2 = ps[i];
        
        auto d = (p.x - p_1.x)*(p_2.y - p_1.y) - (p.y - p_1.y)*(p_2.x - p_1.x);
        if (d == 0) {
            int x_1, x_2, y_1, y_2;
            tie(x_1, x_2) = minmax(p_1.x, p_2.x);
            tie(y_1, y_2) = minmax(p_1.y, p_2.y);
            // on segment
            return p.x >= x_1 && p.x <= x_2 && p.y >= y_1 && p.y <= y_2;
        } 
        int sign_2 = d > 0 ? 1 : -1;
        // sign change
        if (sign_1 + sign_2 == 0) {
            return false;
        }
        sign_1 = sign_2;
        p_1 = p_2;
        }
    return true;
}

vector<Point> ReadPoints(int N) {
    vector<Point> ps;
    ps.reserve(4*N);
    for (auto i = 0; i < N; ++i) {
        int x_1, y_1, x_2, y_2;
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        ps.emplace_back(x_1, y_1);
        ps.emplace_back(x_1, y_2);
        ps.emplace_back(x_2, y_1);
        ps.emplace_back(x_2, y_2);
    }
    return ps;
}

void Reduce(const vector<Index>& inds, vector<Point>& ps) {
    int j = 0;
    for (auto i : inds) {
        ps[j++] =  ps[i];
    }
    ps.resize(j);
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int test_case = 0;
    for (;;) {
        int D, P;
        cin >> D >> P;
        if (D == 0 && P == 0) break;
        
        ++test_case;
        auto dp = ReadPoints(D);
        auto dh = ConvexHull(dp);
        Reduce(dh, dp);
        auto pp = ReadPoints(P);
        auto ph = ConvexHull(pp);
        Reduce(ph, pp);
        
        bool can = true;
        for (auto& p : dp) {
            bool b = IsInConvexPolygon(pp, p);
            if (b) {
                can = false;
                break;
            }
        }
        if (can) {
            for (auto& p : pp) {
                bool b = IsInConvexPolygon(dp, p);
                if (b) {
                    can = false;
                    break;
                }
            }
        }
        cout << "Case " << test_case << ": It is" << (can ? "" : " not") << " possible to separate the two groups of vendors." << endl << endl; 
    }
}

