
#include <iostream>

using namespace std;

int max_h;
int h;

void read() {
    char ch;
    cin >> ch;
    if (ch == 'l') {
        return;
    }
    ++h;
    max_h = max(max_h, h);
    read(); // left
    read(); // right
    --h;
}

int main() {
    
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        max_h = 0;
        h = 0;
        read();
        cout << max_h << endl;
    }
    
}
