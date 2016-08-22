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
#include <iomanip>
#include <memory>
#include <fstream>
#include <bitset>

using namespace std;


using Count = int;
using Int = int;
using Index = int;

template<class T>
struct Grid {
    using value_type = T;
    
    typename std::vector<T>::const_iterator begin() const {
        return grid_.begin();
    }
    typename std::vector<T>::iterator begin() {
        return grid_.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return grid_.end();
    }
    typename std::vector<T>::iterator end() {
        return grid_.end();
    }
    
    Grid() : Grid(0, 0) {}
    Grid(Count row_count, Count col_count)
    :   row_count_(row_count), 
    col_count_(col_count), 
    grid_(row_count*col_count) {}
    
    Grid(Count row_count, Count col_count, const T& value_type) 
    :   row_count_(row_count),
    col_count_(col_count),
    grid_(row_count*col_count, value_type) {}
    
    
    Grid(std::initializer_list<std::vector<T>> list)
    :   Grid(list.size(), list.size() == 0 ? 0 : list.begin()->size()){
        auto b = list.begin();
        for (auto r = 0; r < row_count(); ++r, ++b) {
            std::copy(b->begin(), b->end(), grid_.begin() + r*col_count());
        }
    }
          
    void resize(Count row_count, Count col_count) {
        row_count_ = row_count;
        col_count_ = col_count;
        grid_.resize(row_count*col_count);
    }
    
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
   
    Count cell_count() const { return row_count()*col_count(); } 
    
    T& operator()(Int row, Int col) {
        return grid_[row*col_count_ + col];
    }
    
    const T& operator()(Int row, Int col) const {
        return grid_[row*col_count_ + col];
    }
    
    // function takes in element
    template<class Process>
    void ForEach(Process& proc) {
        for (Index r = 0; r < row_count(); ++r) {
            for (Index c = 0; c < col_count(); ++c) {
                proc((*this)(r, c));
            }
        }
    }
       
           
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
    
    friend struct const_iterator;
    template<class U>
    friend bool operator==(const Grid<U>& g_0, const Grid<U>& g_1);
};



template<class T>
using AdjacencyList = std::vector<std::vector<T>>;

using NodeAdjacencyList = AdjacencyList<Index>;
using Edge = std::array<Index, 2>;

NodeAdjacencyList EdgesToAdjacencyList(const std::vector<Edge>& edges, size_t node_count);





// struct provides access on reading. 
// const prevents alternating variables 
// immutable class
// like wrapper
// can't use unique_ptr here or will be unable to copy
template <class NodeAdjacencyListPtr>
struct Graph {
    
    NodeAdjacencyListPtr adjacency_list_;
    
    Graph(NodeAdjacencyListPtr adj_list) : adjacency_list_(adj_list) {}  
    
    Count degree(Index i) const {
        return (*adjacency_list_)[i].size();
    }
    
    const std::vector<Index>& adjacent(Index i) const {
        return (*adjacency_list_)[i];
    }
    
    Count node_count() const {
        return adjacency_list_->size();
    }
};



template<class Process, class AdjacencyListPtr>
void BFS(const Graph<AdjacencyListPtr>& gr, vector<Index> vs, Process& pr) {
    std::queue<Index> q;
    Count c = gr.node_count();
    std::vector<bool> visited(c, false);
    for (auto v : vs) {
        visited[v] = true;
        q.push(v);
    }
    while (!q.empty()) {
        Index v = q.front();
        q.pop();
        // should we also pass from where we came from
        bool b = pr(v);
        if (b) return;
        for (Index w : gr.adjacent(v)) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }
}


template<class Process, class AdjacencyListPtr> 
void BFS_LateRevisit(const Graph<AdjacencyListPtr>& gr, vector<Index> vs, Process& pr) {
    std::queue<Index> q;
    Count c = gr.node_count();
    std::vector<bool> visited(c, false);
    for (auto v : vs) {
        visited[v] = true;
        q.push(v);
    }
    while (!q.empty()) {
        Index v = q.front();
        q.pop();
        bool b = pr(v);
        if (b) {
            q.push(v);
            continue;
        }
        for (Index w : gr.adjacent(v)) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }
    
}


using P = array<int, 2>;

struct S {
    int child;
    P parents;
};




template<class T = Index>
class Range {
public:
    class Iterator : std::iterator<std::input_iterator_tag, T> {
    public:
        Iterator(const Range& range, T current) 
        : range_(range), current_(current) {
            // just copied that lol
            if (range_.step_*(current_-range_.last_) > 0) current_ = range_.last_;
        }
        const T operator*() const { return current_; }
        bool operator==(const Iterator& it) const {
            return current_ == *it;
        }
        bool operator!=(const Iterator& it) const {
            return current_ != *it;
        }
        Iterator& operator++() {
            current_ += range_.step_;
            if (range_.step_*(current_-range_.last_) > 0) current_ = range_.last_;
            return *this;
        }
        Iterator operator++(int) { 
            Iterator it(*this); 
            operator++(); 
            return it;
        }
    private:
        const Range& range_;
        T current_;
    };
    
    friend class Iterator;
    
    Range(T last) : first_(0), last_(last), step_(1) {}
    Range(T first, T last, T step = 1)
    : first_(first), last_(last), step_(step) {}
    
    Iterator begin() const { return Iterator(*this, first_); }
    Iterator end()   const { return Iterator(*this, last_); }
    
    Index begin_index() const { return first_; }
    Index end_index() const { return last_; } 
    
private:
    T first_, last_, step_;
};

// it's gets so complicated at that point.


NodeAdjacencyList ToAdjList(const vector<P>& arr, const vector<bool>& has_parent) {
    NodeAdjacencyList list(arr.size());
    for (auto i = 0; i < arr.size(); ++i) {
        if (has_parent[i]) {
            list[i].push_back(arr[i][0]);
            list[i].push_back(arr[i][1]);
        }
    }
    return list;
}



template<class Index>
AdjacencyList<Index> Reverse(const AdjacencyList<Index>& adj) {
    int V = adj.size();
    AdjacencyList<Index> adj_new(V);
    for (int i = 0; i < V; ++i) {
        for (int j : adj[i]) {
            adj_new[j].push_back(i);
        }
    }
    return adj_new;
}

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList* ptr) {
    return Graph<const NodeAdjacencyList*>(ptr);
}

Graph<const NodeAdjacencyList*> CreateGraph(const NodeAdjacencyList& ptr) {
    return CreateGraph(&ptr);
}


template<Count MAX_MEMBERS>
class Relates {
public:
    Relates(Count member_count) : ancestors_(member_count) {}

    void AddAncestor(Index ancestor) {
        ancestors_[ancestor].set(ancestor);
    }
    
    void AddRelation(Index child, Index parent) {
        ancestors_[child] |= ancestors_[parent];
    }
    
    void ComputeRelatives() {
        for (Index i_1 = 0; i_1 < ancestors_.size(); ++i_1) {
            for (Index i_2 = i_1; i_2 < ancestors_.size(); ++i_2) {
                if ((ancestors_[i_1] & ancestors_[i_2]).any()) {
                    related_(i_1, i_2) = related_(i_2, i_1) = true;
                }
            }
        }
    }
    
    bool related(Index i_1, Index i_2) {
        return related_(i_1, i_2);
    }
    
    Grid<int> related_{MAX_MEMBERS, MAX_MEMBERS, false};
    vector<bitset<MAX_MEMBERS>> ancestors_;
};



class RelationshipDegree {

    const double UNKNOWN = -1;
    static constexpr Count MAX_MEMBERS = 300;
    
public:
    
    RelationshipDegree(int member_count, int have_parents_count) 
        : member_count_(member_count), have_parents_count_(have_parents_count), 
            parents_(member_count), has_parents_(member_count, false), level_(member_count),
            degree_(member_count, member_count, UNKNOWN), related_(member_count_) {}
    
    
    double Degree(int i_1, int i_2) {
        if (degree_(i_1, i_2) != UNKNOWN) {
            return degree_(i_1, i_2);
        }
        
        int level_1 = level_[i_1];
        int level_2 = level_[i_2];
        
        // make second as son of the first one (second level should be bigger)
        if (level_2 < level_1) swap(i_1, i_2);
        
        auto p_1 = parents_[i_2][0]; 
        auto p_2 = parents_[i_2][1];
        auto d_1 = Degree(i_1, p_1);
        auto d_2 = Degree(i_1, p_2);
        auto d = 1/2. * (d_1 + d_2);
        AddDegree(i_1, i_2, d);
        return d;
    }
    
    void Precompute() {
        vector<int> base_vertices(member_count_-have_parents_count_);
        Range<> r(member_count_);
        copy_if(r.begin(), r.end(), base_vertices.begin(), [&](Index i) { return !has_parents_[i]; } );
        
        // compute relatives
        for_each(base_vertices.begin(), base_vertices.end(), [&](Index i) { related_.AddAncestor(i); });
        for (Index v = 0; v < member_count_; ++v) {
            if (!has_parents_[v]) continue;
            auto& p = parents_[v];
            related_.AddRelation(v, p[0]);
            related_.AddRelation(v, p[1]);
        }
        related_.ComputeRelatives();
        FillUnrelated();
        
        // compute levels
        auto adj_list = Reverse(ToAdjList(parents_, has_parents_));
        auto graph = CreateGraph(adj_list);
        
        auto handler = [&](Index v) { return BFS_Handler(v); };
        BFS_LateRevisit(graph, base_vertices, handler);
    }
    
    
    void AddParents(Index v, const P& p) {
        has_parents_[v] = true;
        parents_[v] = p;
    }

private:

    void FillUnrelated() {
        for (auto r = 0; r < member_count_; ++r) {
            for (auto c = r; c < member_count_; ++c) {
                if (r == c) {
                    AddDegree(r, c, 100);
                } else if (!related_.related(r, c)) {
                    AddDegree(r, c, 0);
                }
            }
        }
    }

    bool BFS_Handler(Index v) {
        // level is always unknown first time
        if (!has_parents_[v]) {
            level_[v] = 0;
            return false;
        } 
        auto ps = parents_[v];
        if (level_[ps[0]] == -1 || level_[ps[1]] == -1) {
            return true;
        }
        level_[v] = 1 + max(level_[ps[0]], level_[ps[1]]);
        return false;
    }

    void AddDegree(Index i_1, Index i_2, double d) {
        degree_(i_1, i_2) = degree_(i_2, i_1) = d;
    }

    Count member_count_;
    Count have_parents_count_;
    vector<P> parents_;
    vector<bool> has_parents_;
    vector<int> level_;
    Grid<double> degree_;
    Relates<MAX_MEMBERS> related_;
    
};


// so we get grid of those guys;
// we place negatives at the beginging;
// when we open more values we place it there;
// recursive calles are going to be expensive but we should be fine.
// 


struct Numb {
	bigint number;
	Count shift;
}

void Bring(Numb& n, Count sh) {
	for (auto i = n.shift; i <= sh; ++i) {
		Mul(n.number, 10);
	}
	n.shift = sh;
}

Numb Sum(const Numb& n_1, const Numb& n_2) {
	Numb res;
	auto m = max(n_1.shift, n_2.shift);
	Bring(n_1, m);
	Bring(n_2, m);
	res.numb = sum(n_1.number, n_2.number);
	res.shift = m;
	return res;
}

void DivideBy2(Numb& n) {
	if (n.number.remainder(2) != 0) {
		n.number.mul(10);
		++n.shift;
	}
	n.number.divide(2);
}

// something like this
void IsDegreeComputed(Index i_1, Index i_2) {
 	return !degree(i_1, i_2).IsNegative();
}

// d_1, d_2
// s = Sum(d_1, d_2)
// s.DivideBy2();
// return s;
// from recursive method should return reference to the object;
// shouldn't be a big deal

// how to output stuff...
void Print(const Numb& n) {
	
	// we may try to divide first
	if (n.shift == 0) {
		// it's 0 or 1
		
	} else {
		while (n.number.remainder(10) == 0) {
			n.number.divide(10);
			--n.shift;
		}
		
		cout << "0.";
		auto pred_zeros = n.shift - n.number.digit_count();
		for (auto i = 0; i < pred_zeros; ++i) {
			cout << "0";
		}
		cout << n.number;
	}
}

template<class T>
Count CountDigits(T t) {
	Count count = 0;
	while (t != 0) {
		t /= 10;
		++count;
	}
	return count;
}
 



void solve(istream& cin, ostream& cout) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int N, K;
        cin >> N >> K;
        RelationshipDegree rd(N, K);
        
        for (auto i = 0; i < K; ++i) {
            Index ch;
            P p;
            cin >> ch; 
            --ch;
            cin >> p[0] >> p[1];
            --p[0]; 
            --p[1];
            rd.AddParents(ch, p);
        }
        
        rd.Precompute();
        
        int M;
        cin >> M;
        for (auto i = 0; i < M; ++i) {
            int m_1, m_2;
            cin >> m_1 >> m_2;
            --m_1;
            --m_2;
            cout << rd.Degree(m_1, m_2) << '%' << endl;
        }
    }    
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    //ifstream in("../in.txt");
    solve(cin, cout);
}


// we have to find exact degree and seems like double won't work for this one

// we have to think about test cases
// there are a lot of divisions by two


// if i start with very big integer and try to later find out float part




