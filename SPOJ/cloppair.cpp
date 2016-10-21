// A divide and conquer program in C/C++ to find the smallest distance from a
// given set of points.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <limits>


using namespace std;

// A structure to represent a Point in 2D plane
struct Point
{
    int64_t x, y;
};

struct R {
    int i_1, i_2;
    int64_t dist = numeric_limits<int64_t>::max();
    
    R() {}
    R(int i_1, int i_2, int64_t dist) 
    : i_1(i_1), i_2(i_2), dist(dist) {}
    
    void OrderIndices() {
        i_1 = min(i_1, i_2);
        i_2 = max(i_1, i_2);
    }
};

bool operator<(const R& r, int64_t d) {
    return r.dist < d;
}
bool operator<(const R& r_1, const R& r_2) {
    return r_1.dist < r_2.dist;
}
bool operator<(int64_t d, const R& r) {
    return d < r.dist;
}


/* Following two functions are needed for library function qsort().
 Refer: http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */

// Needed to sort array of points according to X coordinate
int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

// A utility function to find the distance between two points
int64_t dist(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y);
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
R bruteForce(Point P[], int n)
{
    R min;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min) {
                min = {i, j, dist(P[i], P[j])};
            }
    return min;
}

// A utility function to find minimum of two double values
int64_t min(int64_t x, int64_t y)
{
    return (x < y)? x : y;
}

// A utility function to find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted accordint to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times
R stripClosest(Point strip[], int inds[], int size, R d)
{
    R min = d;  // Initialize the minimum distance as d
    
    qsort(strip, size, sizeof(Point), compareY); 
    
    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min) {
                min = {inds[i], inds[j], dist(strip[i], strip[j])};
            }
    
    return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
R closestUtil(Point P[], int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(P, n);
    
    // Find the middle point
    int mid = n/2;
    Point midPoint = P[mid];
    
    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    R dl = closestUtil(P, mid);
    R dr = closestUtil(P + mid, n-mid);
    
    // Find the smaller of two distances
    R d = min(dl, dr);
    
    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
    int inds[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d) {
            strip[j] = P[i];
            inds[j] = i;
            j++;
        }
    
    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, inds, j, d) );
}

// The main functin that finds the smallest distance
// This method mainly uses closestUtil()
R closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compareX);
    
    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(P, n);
}

// Driver program to test above functions
int main()
{
    int N;
    cin >> N;
    Point P[N];
    for (int i = 0; i < N; ++i) {
        cin >> P[i].x >> P[i].y;
    }
    auto r = closest(P, N);
    cout << r.i_1 << ' ' << r.i_2 << ' ' << fixed << setprecision(6) << sqrt(r.dist); 
    return 0;
}




// this one passed

/*
 USER: zobayer
 TASK: CLOPPAIR
 ALGO: divide and conquer
 */

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long i64;
typedef struct { int x, y, i; } Point;

const int MAX = 56384;
const i64 INF = 1LL<<60;
const double EPS = 1e-9;

int flag[MAX];

inline i64 sq(const i64 &x) {
    return x*x;
}

inline i64 sqdist(const Point &a, const Point &b) {
    return sq(a.x-b.x) + sq(a.y-b.y);
}

inline bool byX(const Point &a, const Point &b) {
    return ((a.x==b.x)? a.y < b.y : a.x < b.x);
}

inline bool byY(const Point &a, const Point &b) {
    return ((a.y==b.y)? a.x < b.x : a.y < b.y);
}

inline void presort(Point *P, Point *X, Point *Y, int n) {
    for(int i = 0; i < n; i++) X[i] = Y[i] = P[i];
    sort(X, X+n, byX);
    sort(Y, Y+n, byY);
}

inline i64 closestPair(Point *X, Point *Y, int n, int &px, int &py) {
    if(n == 1) return INF;
    if(n == 2) {
        px = X[0].i, py = X[1].i;
        return sqdist(X[0], X[1]);
    }
    
    int i, j, k, n1, n2, ns, m = n >> 1, px1, py1, px2, py2;
    Point Xm = X[m-1], *XL, *XR, *YL, *YR, *YS;
    XL = new Point[m], YL = new Point[m];
    XR = new Point[m+1], YR = new Point[m+1];
    YS = new Point[n];
    i64 lt, rt, dd, tmp;
    
    for(i = 0; i < m; i++) XL[i] = X[i], flag[X[i].i] = 0;
    for(; i < n; i++) XR[i - m] = X[i], flag[X[i].i] = 1;
    for(i = n2 = n1 = 0; i < n; i++) {
        if(!flag[Y[i].i]) YL[n1++] = Y[i];
        else YR[n2++] = Y[i];
    }
    
    lt = closestPair(XL, YL, n1, px1, py1);
    rt = closestPair(XR, YR, n2, px2, py2);
    if(lt < rt) dd = lt, px = px1, py = py1;
    else dd = rt, px = px2, py = py2;
    
    for(i = ns = 0; i < n; i++)
        if(sq(Y[i].x - Xm.x) < dd)
            YS[ns++] = Y[i];
    for(j = 0; j < ns; j++) {
        for(k = j + 1; k < ns && sq(YS[k].y - YS[j].y)+EPS < dd; k++) {
            tmp = sqdist(YS[j], YS[k]);
            if(dd > tmp) {
                dd = tmp;
                px = YS[j].i, py = YS[k].i;
            }
        }
    }
    
    delete[] XL; delete[] XR;
    delete[] YL; delete[] YR;
    delete[] YS;
    return dd;
}

Point P[MAX], X[MAX], Y[MAX];

int main() {
    int i, n, px, py;
    i64 ret;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d %d", &P[i].x, &P[i].y);
        P[i].i = i;
    }
    presort(P, X, Y, n);
    ret = closestPair(X, Y, n, px, py);
    if(px > py) swap(px, py);
    printf("%d %d %.6lf\n", px, py, sqrt((double)ret) + 1e-9);
    return 0;
}


