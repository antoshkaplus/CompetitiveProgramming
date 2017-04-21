// unable to send due to c++14 not supported

#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

using Index = int;



template<class Val, class Op>
class RB_Tree {
    
public:
    struct Node;
    
    using UN = std::unique_ptr<Node>;
    
    struct Node {
        
        UN left;
        UN right;
        
        Val val;
        Val op;
        // color can replace with col, size with sz
        bool color;
        int size;
        
        Node(Val val, bool color, int size)
        : val(val), op(val), color(color), size(size) {}  
    };
    
    static const bool RED = true;
    static const bool BLACK = false;
    
    static bool red(const UN& n) {
        if (!n) return false;
        return n->color;
    }
    
    static int size(const UN& n) {
        if (!n) return 0;
        return n->size;
    }
    
    void updateAt(UN& n, Index idx, const Val& val) {
        auto left_sz = size(n->left);
        if (idx < left_sz) {
            updateAt(n->left, idx, val);
        } else if (idx > left_sz) {
            idx -= left_sz + 1;
            updateAt(n->right, idx, val);
        } else {
            n->val = val;
        }
        n->op = op(n->left, n->right, n);
    }
    
    
    static Val& getAt(UN& n, Index idx) {
        auto x = n.get();
        while (x != nullptr) {
            auto left_sz = size(x->left);
            if (idx < left_sz) {
                x = x->left.get();
            } else if (idx > left_sz) {
                idx -= size(x->left) + 1;
                x = x->right.get();
            } else {
                return x->val;
            }
        }
        throw std::runtime_error("element is not found");
    }
    
    static Val& get(UN& n, const Val& val) {
        
        auto x = n.get();
        while (x != nullptr) {
            if (x->val < val) {
                x = x->left;
            } else if (x->val > val) {
                x = x->right;
            } else {
                return x->val;
            }
        }
        throw std::runtime_error("element is not found");
    }
    
    static Index getIndex(UN& n, const Val& val) {
        Index idx = 0;
        auto x = n.get();
        while (x != nullptr) {
            if (x->val < val) {
                idx += size(x->left) + 1;
                x = x->right.get();
            } else if (x->val > val) {
                x = x->left.get();
            } else {
                idx += size(x->left); 
                return idx;
            }
        }
        throw std::runtime_error("element is not found");
    }
    
    RB_Tree(Op op) : op_(op) {}
    
    int size() const {
        return size(root_);
    }
    
    bool empty() const {
        return !root_;
    }
    
    Val& get(const Val& val) {
        return get(root_, val);
    }
    
    Val& getAt(Index idx) {
        return getAt(root_, idx);
    }
    
    Index getIndex(const Val& val) {
        return getIndex(root_, val);
    }
    
    void updateAt(Index idx, const Val& val) {
        updateAt(root_, idx, val);
    }
    
    void put(UN& h, const Val& val) { 
        if (!h) return h.reset(new Node(val, RED, 1));
        
        if (val < h->val) {
            put(h->left, val);
        } else { 
            put(h->right, val);
        } 
        ++h->size;
        h->op = op_(h->op, val);
        
        if (red(h->right) && !red(h->left))	rotateLeft(h);
        if (red(h->left) && red(h->left->left)) rotateRight(h);
        if (red(h->left) && red(h->right)) flipColors(h);
        
    }
    
    void putAt(UN& h, Index pos, Val val) {
        if (!h) return h.reset(new Node(val, RED, 1));
        
        if (pos <= size(h->left)) {
            putAt(h->left, pos, val);
        } else { 
            pos -= size(h->left) + 1;
            putAt(h->right, pos, val);
        } 
        ++h->size;
        h->op = op_(h->op, val);
        
        if (red(h->right) && !red(h->left))	rotateLeft(h);
        if (red(h->left) && red(h->left->left)) rotateRight(h);
        if (red(h->left) && red(h->right)) flipColors(h);
    }
    
    void rotateLeft(UN& h) {
        UN x = std::move(h->right);
        h->right = std::move(x->left);
        x->left = std::move(h);
        x->color = x->left->color;
        x->left->color = RED;
        x->size = x->left->size;
        x->left->size = size(x->left->left) + size(x->left->right) + 1;
        x->left->op = op(x->left->left, x->left->right, x->left);
        x->op = op(x->left, x->right, x);
        h = std::move(x);
    }
    
    void rotateRight(UN& h) {
        UN x = std::move(h->left);
        h->left = std::move(x->right);
        x->right = std::move(h);
        x->color = x->right->color;
        x->right->color = RED;
        x->size = x->right->size;
        x->right->size = size(x->right->left) + size(x->right->right) + 1;
        x->right->op = op(x->right->left, x->right->right, x->right);
        x->op = op(x->left, x->right, x);
        h = std::move(x);
    }
    
    void flipColors(UN& h) {
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }
    
    void put(Val val) {
        put(root_, val);
        root_->color = BLACK;
    }
    
    void putAt(Index pos, Val val) {
        putAt(root_, pos, val);
        root_->color = BLACK;
    }
    
    template<class Func>
    void forEach(Func func) {
        std::function<void(UN&)> call = [&](UN& n) {
            if (n) {
                call(n->left);
                func(n->val);
                call(n->right);
            }
        };
        call(root_);
    }
    
    Val op(UN& n_1, UN& n_2, UN& n_3) {
        Val v = n_3->val;
        if (n_1) v = op_(v, n_1->op);
        if (n_2) v = op_(v, n_2->op);
        return v;
    }
    
    // maybe nothing at all
    Val query(UN& n, Index pos_1, Index pos_2) {
        auto sz_left = size(n->left);
        
        auto left_1 = pos_1 < sz_left;
        auto left_2 = pos_2 < sz_left;
        
        if (left_1 && left_2) {
            return query(n->left, pos_1, pos_2);
        }
        
        auto mid_1 = pos_1 == sz_left;
        auto mid_2 = pos_2 == sz_left;
        
        if (left_1) {
            auto v = op_(n->val, queryLeft(n->left, pos_1));
            if (!mid_2) {
                v = op_(v, queryRight(n->right, pos_2-sz_left-1));
            }
            return v;
        }
        
        // not left_1 => not left_2
        
        if (mid_2) {
            return n->val;
        }
        
        if (mid_1) {
            return op_(n->val, queryRight(n->right, pos_2-sz_left-1));
        }
        
        // else everything is on the right
        return query(n->right, pos_1-sz_left-1, pos_2-sz_left-1);
    }
    
    
    Val queryRight(const UN& n, Index pos) {
        if (pos >= size(n->left)) {
            Val op = n->val;
            if (n->left) {
                op = op_(n->left->op, op);
            } 
            if (size(n->left) != pos) {
                op = op_(op, queryRight(n->right, pos-size(n->left)-1));
            }
            return op;
        } else {
            return queryRight(n->left, pos);
        }
    }
    
    
    Val queryLeft(const UN& n, Index pos) {
        if (pos <= size(n->left)) {
            Val op = n->val;
            if (n->right) {
                op = op_(n->right->op, op);   
            }
            if (size(n->left) != pos) {
                op = op_(op, queryLeft(n->left, pos));
            }
            return op;
        } else {
            return queryLeft(n->right, pos-size(n->left)-1);
        }
    }
    
    
    Val query(Index pos_1, Index pos_2) {
        return query(root_, pos_1, pos_2);
    }
    
    
    Op op_;
    UN root_;
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    auto func = [](int i_1, int i_2) {
        return max(i_1, i_2);
    };
    RB_Tree<int, decltype(func)> rb_tree(func);
    string ch;
    int x, y;
    for (auto i = 0; i < N; ++i) {
        cin >> ch >> x >> y;
        if (ch == "A") {
            rb_tree.putAt(y-1, x);
        } else { // ch == "Q"
            printf("%d\n", rb_tree.query(x-1, y-1));
        }
    }
}
