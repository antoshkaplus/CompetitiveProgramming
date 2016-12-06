





class A {
	
	struct Item {
		bool right;
		int val;
		
		bool operator<(const Item& item) const {
			return val < item.val;
		}
	};
	
	// should return segments that are intersected by this one
	// this method is more like insert
	std::vector<Segment> Intersection(const Segment& seg) const {
		int i_1, i_2;
		tie(i_1, i_2) = seg;
		
		// not considered to go before
		auto it_1 = items_.lower_bound(i_1);
		// right after
		auto it_2 = prev(items_.upper_bound(i_2));
		
		if (it_1->right) {
			i_1 = prev(it_1);
		} else {
			// left one
			i_1 = it_1;
		}
		
		
		if (it_2->left) {
			i_2 = next(it_2)
		} else {
			// right
			i_2 = it_2;
		}
		
		// now we have new segment and we remove others
		// we keep values. nothing to do with iterators
		s = seg(i_1, i_2);
		
		
		// very little difference
		vector<Segment> res;
		for (it = i_1; it != i_2+1;) {
			// can't do that
			res.emplace(it, itt = next(it));
			it = next(itt);
		}
		return res;
		
		
		// about find logic
		// what about union find???
		items_.erase(i_1, i_2+1);
		items_.insert(s);
		// how are we going to unite -> easy
		
		// for each segment we may want to have some value??
	}
	
	// how do we include union fund stuff
	void f() {
		
		// we insert new.
		// if no old we just insert. with area 1*.
		// else we insert and unite with old dudes and // we don't do thing right away
		// we 
		
		
		
	}
	
	
	
	
	set<Item> items_;
};


struct Rect {
	int x_1, y_1, x_2, y_2;
};


enum class CarpetEvent {
    Start,
    Finish
};


struct Event {
    CarpetEvent type;
    int x;
    int bot;
    int top;
    
    bool operator<(const Event& ev) const {
        return x < ev.x;
    }
    
};

// segments should be sorted by x_1, and then by x_2 (not length)

vector<Segment> mergeSegments(vector<Segment>& segs) {
    vector<Segment> res;
    res.push_back(segs[0]);
    for (auto i = 1; i < segs; ++i) {
        if (res.back().isIntersect(segs[i])) {
            res.back() = united(res, segs[i]);
        } else {
            res.push_back(segs[i]);
        }
    }
    return res;
}

// looks pretty good...
 
vector<Segment> buildEmptySegments(Segment empty, vector<Segment>& filled) {
    vector<Segment> res;
    for (auto f : filled) {
        // this one is only for first f basically
        if (empty.first() != f.first()) {
            res.push_back(empty.first(), f.first());
        }
        empty.first() = f.last();
    }
    if (empty.first() != empty.last()) {
        res.push_back(empty);
    }
    return res;
}



int main() {
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
        int prev_x = -1;
        vector<Segment> prevEmpty;
        for (auto i = 0; i < events.size(); ++i) {
                
            auto& ev = events[i];
            
            Segment s(ev.bot, ev.top-ev.bot);
            if (ev.type == CarpetEvent::Start) {
                all_segments.push_back();
            } else { // Finish
                all_segments.erase(find(all_segments.begin(), all_segments.end(), s));
            }
            
            // maybe not yet handle and need to pick up more guys
            
            auto merged = mergeSegments(all_segments);
            auto empty = buildEmptySegments({0, N}, merged);
            
            // we have to add areas now
            
            
        }
        
        
        auto rect_ends = rects;
		// ends
		sort(rect_ends.begin(), rect_ends.end());
		
		// while at least one of them is not empty
		// also we should have something like current state. current state is a vector, sorted by y start
		// it also has index of rectangle to close the right one
		
		// so we delete guys and add... that means that we have to use data structure. let say a tree.
		// that way we can insert too.
		
		// after deletion and insertion we unite everything in one thing. we get a bunch of segments.
		// we add segments to online data structure.
		
		// we can use tree or we can try to merge two arrays.
		// merging should be even more efficient.
		while () {
			
			
		}
		
	}
}
