#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>

using namespace std;




const int N_MAX = 20; 

using BS = bitset<N_MAX>;

struct S {
    
    array<uint64_t, 1 << N_MAX> t;
    const vector<vector<int>> fav;
    
    S(const vector<vector<int>>& fav) : fav(fav) {
        t.fill(-1);
    }
    
    // how many ways if have following fillings
    uint64_t solve(int cur_student, BS& taken_subjects) {
        if (cur_student == fav.size()) return 1;
        
        if (t[taken_subjects.to_ulong()] != -1) {
            return t[taken_subjects.to_ulong()];
        }
        
        uint64_t ways = 0;
        for (int s : fav[cur_student]) {
            if (!taken_subjects[s]) {
                taken_subjects.set(s);
                ways += solve(cur_student+1, taken_subjects);
                taken_subjects.reset(s);
            }
        }
        return t[taken_subjects.to_ulong()] = ways;
    }
    
};


int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (auto t = 0; t < T; ++t) {
        int N; 
        cin >> N;
        vector<vector<int>> fav(N);
        for (auto& f : fav) {
            for (int i = 0; i < N; ++i) {
                int b;
                cin >> b;
                if (b == 1) f.push_back(i);
            }
        }
        BS b;
        uint64_t res = S(fav).solve(0, b);
        cout << res << endl;
    }
    
    return 0;
}




