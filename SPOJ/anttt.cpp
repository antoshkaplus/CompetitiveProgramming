#include <tuple>
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
using Count = int;
using Index = int;

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

struct Segment {
    Segment() {}
    Segment(const Point& fst, const Point& snd)
    : fst(fst), snd(snd) {}
    Point fst, snd;
    
    void Swap() {
        std::swap(fst, snd);
    }
    
    Segment Swapped() const {
        return Segment(snd, fst);
    }
    
private:
    // are listed in counterclockwise order
    // later should put it outside
    static bool CCW(const Point& A, const Point& B, const Point& C) {
        return (C.y-A.y) * (B.x-A.x) > (B.y-A.y) * (C.x-A.x);
    }
    
public:
    
    bool Intersect(const Segment& s) const {
        return CCW(fst, s.fst, s.snd) != CCW(snd, s.fst, s.snd) && 
        CCW(fst, snd, s.fst) != CCW(fst, snd, s.snd);
    }
    
    bool Lie(Point q) const
    {
    Int x_min, x_max, y_min, y_max;
    std::tie(x_min, x_max) = std::minmax(fst.x, snd.x);
    std::tie(y_min, y_max) = std::minmax(fst.y, snd.y);
    return ((q.x - fst.x)*(snd.y - fst.y) == (q.y - fst.y)*(snd.x - fst.x) &&
            q.x <= x_max && q.x >= x_min && q.y <= y_max && q.y >= y_min);
    }
    
    bool IntersectOrLie(const Segment& s) const {
        int o1 = Orientation(fst, snd, s.fst);
        int o2 = Orientation(fst, snd, s.snd);
        int o3 = Orientation(s.fst, s.snd, fst);
        int o4 = Orientation(s.fst, s.snd, snd);
        
        // General case
        if (o1 != o2 && o3 != o4)
            return true;
        
        // Special Cases
        // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == 0 && Lie(s.fst)) return true;
        
        // p1, q1 and p2 are colinear and q2 lies on segment p1q1
        if (o2 == 0 && Lie(s.snd)) return true;
        
        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == 0 && s.Lie(fst)) return true;
        
        // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == 0 && s.Lie(snd)) return true;
        
        return false; // Doesn't fall in any of the above cases
    }
    
private:
    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int Orientation(Point p, Point q, Point r) const
    {
    // See 10th slides from following link for derivation of the formula
    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
    int val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
    }
    
};




class DisjointSet {
public:
    DisjointSet() {}
    DisjointSet(Count element_count) {
        Init(element_count);
    }
    
    void Init(Count element_count) {
        set_count_ = element_count;
        data_.resize(element_count);
        size_.resize(element_count);
        Reset();
    }
    
    void Reset() {
        std::iota(data_.begin(), data_.end(), 0);
        fill(size_.begin(), size_.end(), 1);
    }
    
    void Unite(Index i_0, Index i_1) {
        --set_count_;
        Index
        r_0 = root(i_0),
        r_1 = root(i_1);
        // will join r_0 to r_1, so r_1 height should be bigger
        if (size_[r_0] > size_[r_1]) {
            std::swap(r_0, r_1);
        }
        data_[r_0] = r_1;
        size_[r_1] += size_[r_0];
        
    }
    
    Index Add() {
        Count sz = data_.size();
        data_.resize(sz + 1);
        size_.resize(sz + 1);
        data_.back() = sz;
        size_.back() = 1;
        ++set_count_;
        return sz;
    }
    
    bool is_separate(Index i_0, Index i_1) {
        return root(i_0) != root(i_1);
    }
    
    Index root(Index i) {
        while (i != data_[i]) {
            i = data_[i] = data_[data_[i]];
        }
        return i;
    }
    
    size_t size() {
        return data_.size();
    }
    
    Count set_count() {
        return set_count_;
    }
    
private:
    Count set_count_;
    std::vector<Index> data_;
    // how many elements in set with index, if index is root
    std::vector<size_t> size_;
}; 





int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N, M;
        cin >> N >> M;
        // read all segments
        vector<Segment> segs(N);
        for (int i = 0; i < N; ++i) {
            Point p_1, p_2;
            cin >> p_1.x >> p_1.y >> p_2.x >> p_2.y;
            segs[i] = Segment{p_1, p_2};
        }
        
        DisjointSet set(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (segs[i].IntersectOrLie(segs[j])) {
                    set.Unite(i, j);
                }
            }
        }
        
        for (int i = 0; i < M; ++i) {
            int i_1, i_2;
            cin >> i_1 >> i_2;
            --i_1; --i_2;
            cout << (set.is_separate(i_1, i_2) ? "NO" : "YES") << endl;
        }
    }
}

