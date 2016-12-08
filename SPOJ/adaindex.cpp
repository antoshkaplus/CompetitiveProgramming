
#include <memory>
#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;


struct TernarySearchTree {
    
    struct Node;
    
    using UN = unique_ptr<Node>;
    
    struct Node {
        Node(char ch) : ch(ch) {}
        
        char ch;
        // we could store word end as a node
        // but that makes difficult to count strings with same prefix
        
        // we don't store 0 guy
        int wordEnd = 0;
        int eqSz = 0;
        UN loKid;
        UN eqKid;
        UN hiKid;
    };
    
    
    static int search(const UN& n, const char* s) {
        if (!n) return 0; 
        if (*s < n->ch) return search(n->loKid, s);
        if (*s > n->ch) return search(n->hiKid, s);
        // eq
        if (*(++s) == 0) {
            return n->eqSz + n->wordEnd;
        }
        return search(n->eqKid, s);
    }
    
    static void traverse(const UN& n) {
        if (!n) return;
        cout << "ch: " << n->ch << " end: " << n->wordEnd << endl;
        cout << "lo: " << endl;
        traverse(n->loKid);
        
        cout << "eq: " << n->eqSz << endl; 
        traverse(n->eqKid);
        
        cout << "hi: " << endl;
        traverse(n->hiKid);
    }
    
    
    // you can't come here with 0
    static void insert(UN& n, const char* s) {
        if (!n) {
            n.reset(new Node(*s));
        }
        
        if (*s < n->ch) {
            insert(n->loKid, s);
        } else if (*s == n->ch) {
            
            if (*(s+1) != 0) {
                insert(n->eqKid, ++s);
                ++n->eqSz;
            } else {
                ++n->wordEnd;
            }
            
        } else {
            insert(n->hiKid, s);
        }
    }
    
    
    int search(const char* s) const {
        return search(root, s);
    }
    
    void insert(const char* s) {
        insert(root, s);
    }
    
    void traverse() const {
        traverse(root);
    }
    
private:
    UN root;
    
};


int main() {
    std::ios_base::sync_with_stdio(false);
    ifstream cin("../in.txt"); 
    int N, Q;
    cin >> N >> Q;
    TernarySearchTree tree;
    string str;
    for (auto i = 0; i < N; ++i) {
        cin >> str;
        tree.insert(str.c_str());
    }
    //tree.traverse();
    for (auto i = 0; i < Q; ++i) {
        cin >> str;
        // number of words that have this prefix
        //cout << str << endl;
        auto count = tree.search(str.c_str());
        cout << count << endl;
    }
}



