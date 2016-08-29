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
#include <cassert>

using namespace std;


using Count = int;
using Int = int;
using Index = int;


// number of digits in int 0 is 0
template<class T>
Count CountDigits(T t) {
    Count count = 0;
    while (t != 0) {
        t /= 10;
        ++count;
    }
    return count;
}


struct bigint {
    
    bigint() {}
    bigint(const std::string& s) {
        auto s_i_begin = 0;
        while (std::isspace(s[s_i_begin])) {
            ++s_i_begin;
        }
        
        is_negative_ = false;
        if (s[s_i_begin] == '-') is_negative_ = true;
        if (s[s_i_begin] == '-' || s[s_i_begin] == '+') ++s_i_begin;
        
        Count n = 0;
        while (std::isdigit(s[s_i_begin + n])) {
            ++n;
        }
        init_words(s.c_str()+s_i_begin, n);
    }  
    
    bigint(int small) {
        is_negative_ = false;
        if (small == 0) return;
        words_.push_back(small);
    }
    
    void init_words(const char* s, Count n) {
        if (n == 0) {
            words_.resize(1);
            words_[0] = 0;
        }
        
        auto w_count = n/kWordDigitCount;
        auto rem = n%kWordDigitCount;
        char buf[kWordDigitCount+1]; // 0 character 
        auto assign = [&](const char* str, Count str_n, Index w_i) {
            std::memcpy(buf, str, str_n*sizeof(char));
            buf[str_n] = '\0';
            words_[w_i] = kStrToWord(buf);
        };
        if (rem > 0) { ;
            words_.resize(w_count+1);
            assign(s, rem, w_count);
        } else {
            words_.resize(w_count);
        }
        for (Int w_i = 0, s_i = (Int)n-kWordDigitCount; 
             w_i < w_count; ++w_i, s_i-=kWordDigitCount) {
            assign(s+s_i, kWordDigitCount, w_i);
        }
    }
    
    bool is_zero() const {
        return words_.size() == 1 && words_[0] == 0;
    }
    
    Count digit_count() const {
        if (words_.empty()) return 0;
        return CountDigits(words_.back()) + (kWordDigitCount * (words_.size() - 1));
    }
    
    void Sum(const bigint& b) {
        
    }
    
    int Remainder(int small) const {
        return remainder(*this, small);
    }
    
    void Divide(int small) {
        *this = division(*this, small);
    }
    
    
    void Mul(int small_numb) {
        if (words_.empty()) return;
        auto sz = words_.size();
        for (auto i = 0; i < sz; ++i) {
            words_[i] *= small_numb;
        }
        words_.push_back(0);
        for (auto i = 0; i < sz; ++i) {
            ShiftExcessiveRanks(i);
        }
        if (words_.back() == 0) words_.pop_back();
    }

    
private:
    
    void ShiftExcessiveRanks(Index i) {
        auto& w = words_;
        assert(w.size() > i+1);
        w[i+1] += w[i]/kWordBase;
        w[i] %= kWordBase; 
    }
    
    using word_type = int64_t;
    
    constexpr static const auto kStrToWord = std::atol;
    static const size_t kWordDigitCount = 9;
    static const word_type kWordBase = 1e+9;
    
    // should ve just use negative
    bool is_negative_;
    std::vector<word_type> words_;
    // how many word should be empty on the right
    Count shift_;
    
    
    friend bigint operator*(const bigint& b_0, const bigint& b_1);
    friend bigint standard_multiplication(const bigint& b_0, const bigint& b_1);
    friend bigint sum(const bigint& b_1, const bigint& b_2);
    friend std::ostream& operator<<(std::ostream& output, const bigint& b);
    friend bigint division(const bigint& b, int small_numb);
    friend int remainder(const bigint& b, int small_numb);
    friend std::string ToString(const bigint& n);
    
    friend bool operator==(const bigint& b_1, const bigint& b_2);
    friend bool operator==(const bigint& b, int small);
    friend bool operator!=(const bigint& b, int small); 
};

// one interface but different implementations???
struct bigint_view {
    
    Count shift_;
    // should be a range kind of
    Index i_begin;
    Index i_end;
    bigint& base;
};


std::string ToString(const bigint& n_const) {
    auto n = n_const; 
    if (n.words_.empty()) {
        return "0";
    }
    std::string s;
    s.reserve(n.words_.size()*bigint::kWordDigitCount);
    while (n != 0) {
        int d = n.Remainder(10);
        s.push_back(d + '0');
        n.Divide(10);
    }
    std::reverse(s.begin(), s.end());
    return s;
}



bigint standard_multiplication(const bigint& b_0, const bigint& b_1) {
    bigint r;
    if (b_0.is_zero() || b_1.is_zero()) {
        r.words_.resize(1, 0);
        return r;
    }
    
    auto& w_0 = b_0.words_;
    auto& w_1 = b_1.words_;
    r.is_negative_ = b_0.is_negative_ ^ b_1.is_negative_; // should be bit operation 
                                                          // b_1 * b_0
                                                          // inner loop should be bigger?
    auto& w_r = r.words_; 
    w_r.resize(w_0.size() + w_1.size(), 0);
    for (auto i = 0; i < w_0.size(); ++i) {
        for (auto j = 0; j < w_1.size(); ++j) {
            w_r[i+j] += w_0[i]*w_1[j];
            w_r[i+j+1] += w_r[i+j]/bigint::kWordBase;
            w_r[i+j] %= bigint::kWordBase; 
        }
    }
    if (w_r.back() == 0) w_r.pop_back();
    return r;
}

//bigint karatsuba_multiplication(const bigint& b_0, const bigint& b_1) {
//    bigint r;
//}



bigint sum(const bigint& b_1, const bigint& b_2) {
    
    auto w_min_p = &b_1.words_;
    auto w_max_p = &b_2.words_;
    if (w_min_p->size() > w_max_p->size()) {
        swap(w_min_p, w_max_p);
    }
    auto& w_min = *w_min_p;
    auto& w_max = *w_max_p; 
    
    auto min_sz = w_min.size();
    auto max_sz = w_max.size();
    
    bigint b_r;
    b_r.is_negative_ = false;
    auto& w_r = b_r.words_;
    w_r = w_max;
    for (auto i = 0; i < min_sz; ++i) {
        w_r[i] += w_min[i];	
    }
    w_r.push_back(0);
    for (auto i = 0; i < max_sz; ++i) {
        b_r.ShiftExcessiveRanks(i);
    }
    if (w_r.back() == 0) w_r.pop_back();
    
    return b_r;
}

bigint division(const bigint& b, int small_numb) {
    bigint bb = b;
    auto& w = bb.words_;
    for (auto i = w.size()-1; i > 0; --i) {
        auto t = w[i] % small_numb;
        w[i] /= small_numb;
        w[i-1] += bigint::kWordBase*t;
        
    }
    w[0] /= small_numb;
    return bb;
}

int remainder(const bigint& b, int small_numb) {
    return b.words_.back() % small_numb;
}

bigint operator*(const bigint& b_0, const bigint& b_1) {
    return standard_multiplication(b_0, b_1);
}


std::ostream& operator<<(std::ostream& output, const bigint& b) {
    auto& w = b.words_;
    if (b.is_negative_ && w.back() != 0) output << '-';
    output << w.back();
    
    for (Int i = (Int)w.size()-2; i >= 0; --i) {
        output.width(bigint::kWordDigitCount);
        output.fill('0');
        output.setf(std::ios::right);
        
        output << w[i];
    }
    output.width(0);
    return output;
}   

bool operator==(const bigint& b_1, const bigint& b_2) {
    return b_1.is_negative_ == b_2.is_negative_ && b_1.words_ == b_2.words_;
}

bool operator==(const bigint& b, int small) {
    return (b.words_.empty() && small == 0) || (b.words_.size() == 1 && b.words_.back() == small);
}

bool operator!=(const bigint& b, int small) {
    return !(b == small);
}



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

struct Numb {
    bigint number;
    Count shift = 0;
    
    Numb() {}
    Numb(int small) : number(small) {}
    
    
    void Reduce() {
        while (number.Remainder(10) == 0) {
            number.Divide(10);
            --shift;
        }
    }
};


ostream& operator<<(ostream& cout, const Numb& n) {
    string s = ToString(n.number);
    if (s == "0") s = "";
    
    auto digit_count = n.number.digit_count();
	auto pred_digits = digit_count - n.shift;
	auto i_s = 0;
    
	for (i_s = 0; i_s < min(digit_count, pred_digits); ++i_s) {
		cout << s[i_s]; 
	}
    for (; i_s < pred_digits; ++i_s) {
        cout << "0";
    }
	
	if (pred_digits <= 0) {
		cout << "0";
	}
	if (n.shift > 0) {
		cout << ".";
	}
	
	auto pred_zeros = n.shift - n.number.digit_count();
	for (auto i = 0; i < pred_zeros; ++i) {
		cout << "0";
	}
    if (i_s < s.size()) {
        cout << s.substr(i_s);
    }
	return cout;
}

void Bring(Numb& n, Count sh) {
    for (auto i = n.shift; i < sh; ++i) {
        n.number.Mul(10);
    }
    n.shift = sh;
}

Numb Sum(Numb& n_1, Numb& n_2) {
    Numb res;
    auto m = max(n_1.shift, n_2.shift);
    Bring(n_1, m);
    Bring(n_2, m);
    res.number = sum(n_1.number, n_2.number);
    res.shift = m;
    return res;
}

void DivideBy2(Numb& n) {
    if (n.number.Remainder(2) != 0) {
        n.number.Mul(10);
        ++n.shift;
    }
    n.number.Divide(2);
}


class RelationshipDegree {

    const double UNKNOWN = -1;
    static constexpr Count MAX_MEMBERS = 300;
    
public:
    
    RelationshipDegree(int member_count, int have_parents_count) 
        : member_count_(member_count), have_parents_count_(have_parents_count), 
            parents_(member_count), has_parents_(member_count, false), level_(member_count),
            degree_(member_count, member_count, UNKNOWN), related_(member_count_) {
        
        
    }
    
    
    Numb& Degree(int i_1, int i_2) {
        if (degree_(i_1, i_2).number != UNKNOWN) {
            return degree_(i_1, i_2);
        }
        
        int level_1 = level_[i_1];
        int level_2 = level_[i_2];
        
        // make second as son of the first one (second level should be bigger)
        if (level_2 < level_1) swap(i_1, i_2);
        
        auto p_1 = parents_[i_2][0]; 
        auto p_2 = parents_[i_2][1];
        auto& d_1 = Degree(i_1, p_1);
        auto& d_2 = Degree(i_1, p_2);
        auto d = Sum(d_1, d_2);
        DivideBy2(d);
        d.Reduce();
        return AddDegree(i_1, i_2, d);
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

    Numb& AddDegree(Index i_1, Index i_2, const Numb& d) {
        return degree_(i_1, i_2) = degree_(i_2, i_1) = d;
    }

    Count member_count_;
    Count have_parents_count_;
    vector<P> parents_;
    vector<bool> has_parents_;
    vector<int> level_;
    Grid<Numb> degree_;
    Relates<MAX_MEMBERS> related_;
    
};


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



struct Test {
	int member_count;
	int base_count;
	int query_count;
	vector<S> children;
	vector<P> queries;
};

Test test(int member_count = -1) {
	default_random_engine rng;
	if (member_count == -1) {
		std::uniform_int_distribution member_distr(2, MAX_MEMBERS);
		member_count = member_distr(rng);
	}
	std::uniform_int_distribution base_distr(2, member_count);
	int base_count = base_distr(rng);
	int sz = member_count - base_count;
	vector<S> children(sz);
	for (auto i = 0; i < sz; ++i) {
		std::uniform_int_distribution d(base_count + i)
		int p_1 = d(rng);
		int p_2 = d(rng);
		auto& ch = children[i];
		ch.child = base_count + i;
		ch.parents = {{p_1, p_2}};
	}
	std::uniform_int_distribution query_distr(1, member_count*member_count);
	int query_count = query_distr(rng);
	vector<P> queries(query_count);
	for (auto i = 0; i < query_count; ++i) {
		int m_1 = member_distr(rng);
		int m_2 = member_distr(rng);
		queries[i] = {{m_1, m_2}};
	}
	return Test{member_count, base_count, query_count, children, queries};	
}

void test() {
	for (auto m : {{ 10, 20, 50, 100, 200, 300 }}) {
		Test t = test(m);
		int K = t.member_count - t.base_count;
		RelationshipDegree rd(t.member_count, t.member_count - t.base_count);
		for (auto& ch : t.children) {
			rd.AddParents(ch.child, ch.parents);
		}
		rd.Precompute();
		for (auto& p : t.queries) {
			Print(rd.Degree(p[0], p[1]));
			cout << '%' << endl;
		}
	}
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    ifstream cin("../in.txt");
    solve(cin, cout);
}

