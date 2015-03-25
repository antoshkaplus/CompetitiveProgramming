
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int MRO_MAX_COUNT = 26*26*26*10;


int MRO[MRO_MAX_COUNT];

struct Item {
    Item() {}
    Item(int resel, int mro) : resel(resel), mro(mro) {}
    int resel;
    int mro;
    bool operator<(const Item& item) const {
        return resel < item.resel;
    }
    bool operator<(const int i) const {
        return resel < i;
    }
};

int mro_key(const string& s) {
    return (s[0]-'A')*26*26*10 +
    (s[1]-'A')*26*10 +
    (s[2]-'A')*10 +
    (s[3]-'0');
}

char key[5];

void key_mro(int i) {
    key[0] = i / (26*26*10) + 'A';
    i %= (26*26*10);
    key[1] = i / (26*10) + 'A';
    i %= (26*10);
    key[2] = i / 10 + 'A';
    key[3] = i % 10 + '0';
}

int item_count = 0;
Item items[100000];

int resel_count = 0;
int resels[100000];


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    key[4] = '\0';
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        cin >> item_count;
        // prepare
        for (int i = 0; i < MRO_MAX_COUNT; ++i) {
            MRO[i] = i;
        }
        string s_0, s_1;
        for (int i = 0; i < item_count; ++i) {
            cin >> s_0 >> s_1;
            items[i] = Item(atoi(s_0.c_str()+2), mro_key(s_1));
        }
        int mro_new_count;
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> s_0 >> s_1;
            MRO[mro_key(s_0)] = mro_key(s_1);
        }
        cin >> resel_count;
        for (int i = 0; i < resel_count; ++i) {
            cin >> s_0;
            resels[i] = atoi(s_0.c_str()+2);
        }
        
        sort(items, items+item_count);
        for (int i_r = 0; i_r < resel_count; ++i_r) {
            Item* t = lower_bound(items, items + item_count, resels[i_r]);
            int p = t->mro, y;
            while (MRO[p] != p) {
                p = MRO[p] = MRO[MRO[p]];
            }
            key_mro(MRO[p]);
            printf("84%09d %s\n", resels[i_r], key);
            
        }
        printf("\n");
    }
}