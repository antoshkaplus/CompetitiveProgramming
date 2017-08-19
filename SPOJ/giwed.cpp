#include <vector>
#include <tuple>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <memory>
#include <algorithm>
#include <sstream>
#include <fstream>


using namespace std;

using Index = int;
using Count = int;
using Int = int;


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
        auto r_0 = root(i_0);
        auto r_1 = root(i_1);
        if (r_0 == r_1) return;
        --set_count_;
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


struct Segment {
    Segment() {}
    Segment(Int origin, Int length) : origin(origin), length(length) {}
    
    
    Segment united(const Segment& s) const {
        Segment r;
        r.origin = min(first(), s.first()); 
        r.length = max(last(), s.last()) - r.origin;
        return r;
    }
    
    bool isIntersect(const Segment& s) const {
        return !(origin >= s.origin + s.length || s.origin >= origin + length); 
    }
    
    bool isInside(const Segment& s) const {
        return origin <= s.origin && origin + length >= s.origin + length;
    }
    
    bool isInside(Int p) const {
        return p >= origin && p <= origin + length;
    }
    
    void set_first(Int first) {
        length += origin - first;
        origin = first;
    }
    
    void set_last(Int last) {
        length = last - origin;
    }
    
    Int first() const {
        return origin;
    }
    
    Int last() const {
        return origin + length;
    }
    
    bool isEmpty() const {
        return length <= 0;
    }
    
    static Segment united(const Segment& s_1, const Segment& s_2) {
        auto origin = min(s_1.origin, s_2.origin);
        auto length = max(s_1.last(), s_2.last()) - origin;
        return {origin, length};
    }
    
    Int origin, length;
};


bool operator==(const Segment& s_0, const Segment& s_1) {
    return s_0.origin == s_1.origin && s_0.length == s_1.length;
}



enum class CarpetEvent {
    Start,
    Finish
};

struct Event {
    CarpetEvent type;
    int x;
    int bot;
    int top;
    
    Event(CarpetEvent type, int x, int bot, int top) 
        : type(type), x(x), bot(bot), top(top) {}
    
    bool operator<(const Event& ev) const {
        return x < ev.x;
    }
    
};



struct EmptyAreas {
	
	EmptyAreas(int height) : height(height) {}
	
	void add(int length, const vector<Segment>& filledSegs) {
        addPrevAreas(length);
        
        // work with new segments
        auto merged = mergeSegments(filledSegs);
        empty = buildEmptySegments({0, height}, merged);
		
		computeEmptyToId();
		areas.resize(ids.size(), 0);
		
		prevEmpty = empty;
		prevEmptyToId = emptyToId;
	}
	
	
	// segments should be sorted by x_1, and then by x_2 (not length)
	vector<Segment> mergeSegments(const vector<Segment>& segs) {
		vector<Segment> res;
		if (segs.empty()) return res;
        
        res.push_back(segs[0]);
		for (auto i = 1; i < segs.size(); ++i) {
			if (res.back().isIntersect(segs[i])) {
				res.back() = Segment::united(res.back(), segs[i]);
			} else {
				res.push_back(segs[i]);
			}
		}
		return res;
	}
	 
	static vector<Segment> buildEmptySegments(Segment empty, vector<Segment>& filled) {
		vector<Segment> res;
		for (auto f : filled) {
			// this one is only for first f basically
			if (empty.first() != f.first()) {
				res.emplace_back(empty.first(), f.first()-empty.first());
			}
			empty.set_first(f.last());
		}
		if (empty.first() != empty.last()) {
			res.push_back(empty);
		}
		return res;
	}

	// empty and emptyToId have same size
	void addPrevAreas(int length) {
		for (int i = 0; i < prevEmpty.size(); ++i) {
			areas[prevEmptyToId[i]] += length*prevEmpty[i].length;
		}
	}

	void computeEmptyToId() {
		emptyToId.resize(empty.size());
        fill(emptyToId.begin(), emptyToId.end(), -1);
        
		int i = 0;
		int j = 0;
		while (i != prevEmpty.size() && j != empty.size()) {
			if (prevEmpty[i].last() <= empty[j].first()) {
				++i;
				continue;
			}
			if (prevEmpty[i].first() >= empty[j].last()) {
				++j;
				continue;
			}
			// intersection
			if (emptyToId[j] == -1) {
				emptyToId[j] = prevEmptyToId[i];
			} else {
				ids.Unite(emptyToId[j], prevEmptyToId[i]);
			}
			if (prevEmpty[i].last() > empty[j].last()) {
				++j;
			} else {
				++i;
			}
		}
		for (auto& k : emptyToId) {
			if (k == -1) k = ids.Add();
		}
	}
	
    // ATTENTION!!! VERY DANGEROUS OPERATION!!! CHANGES STRUCTURE areas GETS SORTED. AVOID!!!
	vector<int> compute() {
        // bring it all together
		for (int i = 0; i < areas.size(); ++i) {
			auto r = ids.root(i);
			if (r != i) {
				areas[r] += areas[i];
				areas[i] = 0;
			}
		}
		sort(areas.begin(), areas.end(), std::greater<int>());
        return areas;
	}
	
	int height;
    
	DisjointSet ids;
	
	vector<Segment> empty;
	vector<Index> emptyToId;
	vector<Segment> prevEmpty;
	vector<Index> prevEmptyToId;
	
	vector<int> areas;
};




int main() {
    ifstream cin("../in.txt");
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		// grid (M(x), N(y)), carpets, pipes
		int M, N, K, L;
		cin >> M >> N >> K >> L;
		vector<Event> events; 
		events.emplace_back(CarpetEvent::Finish, 0, 0, N);
        events.emplace_back(CarpetEvent::Start, M, 0, N);
        
        for (int i = 0; i < K; ++i) {
            // lower left, upper right
			int x_1, y_1, x_2, y_2;
			cin >> x_1 >> y_1 >> x_2 >> y_2;
			events.emplace_back(CarpetEvent::Start, x_1, y_1, y_2);
            events.emplace_back(CarpetEvent::Finish, x_2, y_1, y_2);
		}
		// beginning
		sort(events.begin(), events.end());
		vector<Segment> all_segments;
        all_segments.emplace_back(0, N);
        
		EmptyAreas emptyAreas(N);
		
		int prev_x = 0;
		int i = 0;
		for (; i < events.size();) {
			auto cur_x = events[i].x;
			for (; i < events.size(); ++i) {
				auto& ev = events[i];
				
				if (ev.x != cur_x) break;
				
				Segment s(ev.bot, ev.top-ev.bot);
				if (ev.type == CarpetEvent::Start) {
					all_segments.push_back(s);
				} else { // Finish
					all_segments.erase(find(all_segments.begin(), all_segments.end(), s));
				}
			}
            auto cmp = [](const Segment& s_1, const Segment& s_2) {
                return s_1.origin < s_2.origin || (s_1.origin == s_2.origin && s_1.length < s_2.length);
            };
            sort(all_segments.begin(), all_segments.end(), cmp);
			emptyAreas.add(cur_x - prev_x, all_segments);
			prev_x = cur_x;
        }
        
		auto areas = emptyAreas.compute();
		auto result = accumulate(areas.begin(), areas.begin() + std::min<int>(areas.size(), L), 0);
		cout << result << endl;

	}
}
