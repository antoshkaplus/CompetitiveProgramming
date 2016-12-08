

#include <string>
#include <list>
#include <iostream>
#include <cstdio>

using namespace std;

void slow_solution() {
    std::ios_base::sync_with_stdio(false);
    while(!cin.eof()) {
        list<int> seq;
        // points on element to remove
        list<int>::iterator mid = seq.end();
        for (;;) {
            int x;
            cin >> x;
            if (x == 0) break;
            
            if (x == -1) {
                int sz = seq.size();
                cout << *mid << endl;
                mid = seq.erase(mid);
                
                if (sz%2 == 0) {
                    // everything is where it suppose to be
                } else {
                    if (sz > 1) {
                        --mid;
                    }
                }
                
            } else {
                int sz = seq.size();
                seq.push_back(x);
                if (sz%2 == 0) {
                    if (sz == 0) {
                        mid = seq.begin();
                    } else {
                        ++mid;
                    }
                } else {
                    // everything is fine
                }
            }
        }
        std::string s;
        getline(cin, s);
        cout << endl;
    }
}

void fast_solution() {
    int i,l1=0,l2=0,r1=0,r2=0,n;
    int low[100001],high[100001];
    while(scanf("%d",&n)!= EOF) {
        if(n==0) {
            l1=l2=r1=r2=0;
            printf("\n");
        }
        else if(n == -1) {
            printf("%d\n",low[r1-1]);
            if(r1-l1 > r2-l2)
                r1--;
            
            else {
                low[r1-1] = high[l2];
                l2++;
            }
        }
        else {
            if(r1-l1 > r2-l2) {
                high[r2] = n;
                r2++;
            }
            else {
                if(r1 == 0) {
                    low[r1] = n;
                    r1++;
                }
                else {
                    low[r1] = high[l2];
                    r1++;
                    l2++;
                    high[r2] = n;
                    r2++;
                }
            }
        }
    }
}

int main() {
    fast_solution();
}