
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

struct EmptyAreas {
	
	EmptyAreas(int M, int N) {}
	
	void add(int length, const vector<Segment>& filledSegs) {
		// some data structure would be great here
		auto merged = mergeSegments(filledSegs);
		auto empty = buildEmptySegments({0, N}, merged);
		
		// we have to add areas now
		addAreas(length, prevEmpty, prevEmptyToId, areas);
		
		emptyToId = emptySetIds(ids, prevEmpty, prevEmptyToId, empty);
		areas.resize(ids.size(), 0);
		
		prevEmpty = empty;
		prevEmptyToId = emptyToId;
	}
	
	
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

	// empty and emptyToId have same size
	void addAreas(int length, const vector<Segment>& empty, const vector<Index>& emptyToId vector<int>& idAreas) {
		for (int i = 0; i < empty.size(); ++i) {
			idAreas[emptyToId[i]] += length*empty[i].length;
		}
	}

	vector<Index> emptySetIds(const DisjointSet& ds, const vector<Segment>& prevEmpty, const vector<Index>& prevEmptyToId, const vector<Segment>& empty) {
		vector<Index> emptyToId(empty.size(), -1);

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
				ds.Unite(emptyToId[j], prevEmptyToId[i]);
			}
			if (prevEmpty[i].last() > empty[j].last()) {
				++j;
			} else {
				++i;
			}
		}
		for (auto& k in emptyToId) {
			if (k == -1) k = ds.Add();
		}
		return emptyToId;
	}
	
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
	}
	
	
	DisjointSet ids;
	
	vector<Segment> empty;
	vector<Index> emptyToId;
	vector<Segment> prevEmpty;
	vector<Index> prevEmptyToId;
	
	vector<int> areas;
};



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
        
		EmptyAreas emptyAreas(M, N);
		
		int prev_x = 0;
		int i = 0;
		for (; i < events.size();) {
			cur_x = events[i].x;
			for (; i < events.size(); ++i) {
				auto& ev = events[i];
				
				if (ev.x != cur_x) break;
				
				Segment s(ev.bot, ev.top-ev.bot);
				if (ev.type == CarpetEvent::Start) {
					all_segments.push_back();
				} else { // Finish
					all_segments.erase(find(all_segments.begin(), all_segments.end(), s));
				}
			}
			// we need like very prev x, like real prev x
			emptyAreas.add(cur_x - prev_x, all_segments);
			prev_x = cur_x;
        }
        
		auto areas = emptyAreas.compute();
		auto result = accumulate(areas.begin(), areas.begin() + min(areas.size(), L));
		cout << result << endl;
	}
}
