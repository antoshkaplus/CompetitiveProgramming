





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


int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		// grid, carpets, pipes
		int M, N, K, L;
		cin >> M >> N >> K >> L;
		vector<Rect> rects;
		for (int i = 0; i < K; ++i) {
			int x_1, y_1, x_2, y_2;
			cin >> x_1 >> y_1 >> x_2 >> y_2;
			rects.emplace(x_1, y_1, x_2, y_2);
		}
		// beginning
		sort(rects.begin(), rects.end());
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
