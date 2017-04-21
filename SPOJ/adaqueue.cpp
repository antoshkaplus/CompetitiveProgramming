#include <list>
#include <string>
#include <iostream>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int Q;
    cin >> Q;
    list<int> q;
    string front = "front";
    string back = "back";
    string reverse = "reverse";
    string pushFront = "toFront";
    string pushBack = "push_back";
    
    string cmd;
    int numb = 0;
    for (auto i = 0; i < Q; ++i) {
        cin >> cmd;
        if (cmd == reverse) {
            swap(front, back);
            swap(pushBack, pushFront);
        } else if (cmd == front) {
            if (q.empty()) cout << "No job for Ada?\n";
            else {
                cout << q.front() << "\n";
                q.pop_front();
            }
        } else if (cmd == back) {
            if (q.empty()) cout << "No job for Ada?\n";
            else {
                cout << q.back() << "\n";
                q.pop_back();
            }
        } else if (cmd == pushFront) {
            cin >> numb;
            q.push_front(numb);
        } else if (cmd == pushBack) {
            cin >> numb;
            q.push_back(numb);
        }
    }
}
