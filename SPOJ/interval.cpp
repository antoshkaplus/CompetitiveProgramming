

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
#include <assert.h>
#include <fstream>
#include <random>

using namespace std;


int pow_2(int power) {
    return 1 << power;
}

namespace ant {
    
    using Int = int;
    // index and count should be of type int
    // because 
    // 1) unsigned types increase probability of making a bug
    // 2) lesser type will create problem of casting or being too little
    // 3) bigger type impossible to iterate through
    // the only thing is unsigned integers is good for bitwise operations
    using Count = int; 
    using Index = int;
    using Amount = int;
    using Id = int;
    
    using Long = int64_t;
    using Float = double;
    using Double = double;
    
}


namespace ant {
    
    
    
    template<class T>
    class CompleteBinaryTree  {
        
    public:
        
        CompleteBinaryTree(int leaf_count) {
            int perf_leafs = perfect_leafs(leaf_count);
            int nodes_count = perfect_nodes(perf_leafs) - perf_leafs + leaf_count;
            nodes_.resize(nodes_count);
        }
        
        
        Index left_child(Index parent) {
            Index ch = 2*parent + 1;
            assert(is_child(ch));
            return ch; 
        }
        
        Index right_child(Index parent) {
            Index ch = 2*parent + 2;
            assert(is_child(ch));
            return ch;
        }
        
        bool is_child(Index node) {
            return node < nodes_.size();
        } 
        
        T& node(Index node) {
            return nodes_[node];
        }
        
        const T& node(Index node) const {
            return nodes_[node];
        }
        
        template<class Func>
        void ForEachNode(Func func) {
            for (auto& n : nodes_) {
                func(n);
            }
        }
        
        static Count perfect_leafs(Count leaf_count) {
            // nearest power of 2 for leafs in perfect tree
            Count p = std::ceil(log2(leaf_count));
            return pow_2(p);
        }
        
        static Count perfect_nodes(Count perf_leaf_count) {
            return 2*perf_leaf_count -1;
        }    
        
    private:
        
        vector<T> nodes_;
        
    };
    
    
    
}




namespace ant {
    
    
    // this one is customized for pecial case (check add method)
    // it should look different otherwise probably
    // like when you add, you add to particular value in the tree
    // or something
    
    // add something about taken
    class RangeCount {
        
    public:
        // what about providing some default value.
        RangeCount(ant::Count elem_count)
        : elem_count_(elem_count), perf_leaf_count_(CompleteBinaryTree<int>::perfect_leafs(elem_count)), taken_(elem_count) {
            
            auto func = [](ant::Count& node) { node = 0; };
            taken_.ForEachNode(func);
        }
        
        void AddToRight(int first, int last, int how_many) {
            if (how_many <= 0) return;
            AddToRight(0, first, last, 0, elem_count_-1, how_many, perf_leaf_count_);
        }
        
        int Count(int first, int last) {
            return Count(0, first, last, 0, elem_count_-1, perf_leaf_count_);
        }
        
    private:
        
        void AddToRight(int node_index, int first, int last, int from, int to, int how_many, int perf_leaf_count) {
            assert(perf_leaf_count != 0);
            auto count = (taken_.node(node_index) += how_many);
            if (count == to - from + 1) return;
            
            int perf_leaf_half = perf_leaf_count/2;
            int first_right = from + perf_leaf_half;
            
            if (last < first_right) {
                node_index = taken_.left_child(node_index);
                to = min(first_right - 1, to);
                AddToRight(node_index, first, last, from, to, how_many, perf_leaf_half);
                return;
            }
            
            if (first >= first_right) {
                node_index = taken_.right_child(node_index);
                from = first_right;
                AddToRight(node_index, first, last, from, to, how_many, perf_leaf_half);
                return;
            }
            
            
            // count right free that's in bound
            int r_ch = taken_.right_child(node_index);    
            int r_count = Count(r_ch, first_right, last, first_right, to, perf_leaf_half);
            int r_possible = last - first_right + 1;
            int free = r_possible - r_count;
            if (free >= how_many) {
                AddToRight(r_ch, first_right, last, first_right, to, how_many, perf_leaf_half);
                return;
            } else {
                AddToRight(r_ch, first_right, last, first_right, to, free, perf_leaf_half);
                how_many -= free;
                AddToRight(taken_.left_child(node_index), first, first_right-1, from, first_right-1, how_many, perf_leaf_half);
            }
        }   
        
        
        // we use including
        int Count(int node_index, int first, int last, int from, int to, int perf_leaf_count) {
            
            if (taken_.node(node_index) == to - from + 1) {
                return last - first + 1;
            }
            if (first == from && last == to) {
                return taken_.node(node_index);
            }
            
            int perf_leaf_half = perf_leaf_count/2;
            int first_right = from + perf_leaf_half;
            
            if (last < first_right) {
                // everything on the left
                return Count(taken_.left_child(node_index), first, last, from, min(first_right - 1, to), perf_leaf_half);
            }
            if (first >= first_right) {
                // everything on the right
                return Count(taken_.right_child(node_index), first, last, first_right, to, perf_leaf_half);
            }
            // everything is between
            return Count(taken_.left_child(node_index), first, first_right - 1, from, first_right - 1, perf_leaf_half) + 
            Count(taken_.right_child(node_index), first_right, last, first_right, to, perf_leaf_half);
        }    
        
        int elem_count_;
        int perf_leaf_count_;
        CompleteBinaryTree<ant::Count> taken_;
        
    };
    
    
    
}

struct S {
    int a, b, c;
};


void solve(istream& cin, ostream& cout) {
    std::ios_base::sync_with_stdio(false);
    int test_count;
    cin >> test_count;
    for (int test_index = 0; test_index < test_count; ++test_index) {
        int interval_count;
        cin >> interval_count;
        vector<S> intervals(interval_count);
        for (auto& i : intervals) {
            cin >> i.a >> i.b >> i.c;
        }
        sort(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
            return s_1.b < s_2.b;
        });
        int sub = min_element(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
            return s_1.a < s_2.a;
        })->a;

        for (auto& i : intervals) {
            i.a -= sub;
            i.b -= sub;
        }
        // 0 element is +1
        ant::RangeCount range_count(intervals.back().b + 1);
        for (auto& i : intervals) {
            int count = range_count.Count(i.a, i.b);
            range_count.AddToRight(i.a, i.b, i.c - count);
        }
        cout << range_count.Count(0, intervals.back().b) << endl;
    }
}


ant::Count solve(vector<S> intervals) {
    sort(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
        return s_1.b < s_2.b;
    });
    int sub = min_element(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
        return s_1.a < s_2.a;
    })->a;

    for (auto& i : intervals) {
        i.a -= sub;
        i.b -= sub;
    }
    // 0 element is +1
    ant::RangeCount range_count(intervals.back().b + 1);
    for (auto& i : intervals) {
        int count = range_count.Count(i.a, i.b);
        range_count.AddToRight(i.a, i.b, i.c - count);
    }
    return range_count.Count(0, intervals.back().b);
}



struct Test {
    vector<S> intervals;
    ant::Count result;
};


default_random_engine rng;


// border and how many intervals to take
// how many bound
Test prepare_test_cases(int a, int b, int n) {
    std::uniform_int_distribution<> numb_distr(a, b);
    
    
    vector<S> intervals(n);
    for (auto& s : intervals) {
        auto x_1 = numb_distr(rng);
        auto x_2 = numb_distr(rng);
        tie(s.a, s.b) = minmax(x_1, x_2);
        std::uniform_int_distribution<> how_many_distr(0, s.b - s.a + 1);
        s.c = how_many_distr(rng);
    }
    int left_shift = min_element(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
        return s_1.a < s_2.a;
    })->a;
    for_each(intervals.begin(), intervals.end(), [=](S& s) { 
        s.a -= left_shift;
        s.b -= left_shift;
    });
    
    int last = max_element(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
        return s_1.b < s_2.b;
    })->b; 
    
    vector<bool> taken(last + 1, false); 
    
    sort(intervals.begin(), intervals.end(), [](const S& s_1, const S& s_2) {
        return s_1.b < s_2.b;
    });
    
    
    for (auto& s : intervals) {
        auto present_count = count(taken.begin() + s.a, taken.begin() + s.b + 1, true);
        auto left = s.c - present_count;
        for (auto i = s.b; left > 0 && i >= s.a; --i) {
            if (!taken[i]) {
                taken[i] = true;
                --left;
            }
        }
        assert(left <= 0);
    }
    
    int res = count(taken.begin(), taken.end(), true);
    // now we have to write it somewhere
    
    for_each(intervals.begin(), intervals.end(), [=](S& s) { 
        s.a += left_shift;
        s.b += left_shift;
    });
    
    random_shuffle(intervals.begin(), intervals.end());
    
    return Test{intervals, res};
}

void test() {   
    // starting values
    vector<int> as = { 1, 5, 10, 20, 100 }; 
    vector<int> sizes = { 10, 100, 1000, 10000 };
    for (int s : sizes) {
        uniform_int_distribution<> n_distr(1, s);
        for (int a : as) {
            Test t = prepare_test_cases(a, a+s-1, n_distr(rng));
            auto s_res = solve(t.intervals);
            assert(s_res == t.result);
        }
    }

}


int main(int argc, char **argv) {
    //ifstream in("../in.txt");
    //solve(in, cout);
}



