#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;


#define ST  stack
#define ST_i ST<int>
#define ST_i64 ST<int64_t>
#define ST_ii ST<pair<int, int>>


#define V  vector
#define V_i V<int>
#define V_s V<string>
#define V_b V<bool>
#define V_V_i V<V_i>
#define V_V_b V<V_b>
#define V_ii V<pair<int, int>>

#define P_ii pair<int, int>
#define P   pair

#define M   map
#define M_ii M<int, int>

#define UM unordered_map

#define S_i set<int>
#define S set

#define US unordered_set

#define ODD(n) ((n)%2 != 0) 
#define EVEN(n) ((n)%2 == 0)


// should use regions instead of squares

// 3
struct ConnectingGameDiv2 {
    const int MAX_FILL_COUNT = 1000000;
    
    // best complete filled count when this region used
    UM<char, int> best_used;
    // points that are correspond to this region
    UM<char, V_ii> region_points;
    
    // right most regions
    US<char> right_regions;
    
    V_V_b used;
    V_s board;
    int width;
    int height;
    // which regions did this
    void go(int r, int c, US<char>& regions_inside, int filled_count) {
        char current_region = board[r][c];
        if (regions_inside.count(current_region) == 0) {
            filled_count += region_points[current_region].size();
            regions_inside.insert(current_region);
        }
        if (best_used[current_region] <= filled_count) {
            // no way this way is better
            return;
        }
        if (right_regions.count(current_region) != 0) {
            for (char region : regions_inside) {
                if (best_used[region] > filled_count) best_used[region] = filled_count;
            }
            return;
        }
        
        if (r < height -1) {
            try_out(r + 1, c + 1, regions_inside, filled_count);
            try_out(r + 1, c, regions_inside, filled_count);
        }
        if (r > 0) {
            try_out(r - 1, c + 1, regions_inside, filled_count);
            // with this shit i'm able to go back.. fuck
            try_out(r - 1, c, regions_inside, filled_count);
        }
        try_out(r, c + 1, regions_inside, filled_count);
    }
    
    void try_out(int r, int c, US<char>& regions_inside, int filled_count) {
        if (used[r][c]) return;
        bool need_remove = regions_inside.count(board[r][c]) == 0 ? true : false;
        used[r][c] = true;
        go(r, c, regions_inside, filled_count);  
        used[r][c] = false;
        if (need_remove) regions_inside.erase(board[r][c]);
    }
    
    int getmin(V_s board) {
        this->board = board;
        width = board[0].size();
        height = board.size();
        used.resize(height, V_b(width, false));
        // counting shit
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                char ch = board[r][c];
                region_points[ch].emplace_back(r, c);
            }
            right_regions.insert(board[r][width-1]);
        }
        
        // can avoid sorting if will fill region_points by columns
        for (auto& p : region_points) {
            best_used[p.first] = MAX_FILL_COUNT;
            sort(p.second.begin(), p.second.end(), [](const P_ii& p_0, const P_ii& p_1) {
                return p_0.second > p_1.second;
            });
        }
        
        US<char> regions_inside;
        for (int r = 0; r < board.size(); ++r) {
            try_out(r, 0, regions_inside, 0);
        }
            
        int minimum_filled = MAX_FILL_COUNT;
        for (auto& bu : best_used) {
            if (bu.second < minimum_filled) {
                minimum_filled = bu.second;
            }
        }
        return minimum_filled;
    }
};


// 2
struct PathGameDiv2 {
    V_V_i weight;
    V_s board;
    int min_used;
    
    void go(int r, int c, int used) {
        if (board[r][c] == '#') return;
        if (weight[r][c] <= used) return;
        
        weight[r][c] = used;
        
        if (c == board[0].size() - 1) {
            return;
        }
        if (r == 0) {
            go(r + 1, c, used + 1);
        } else { // r == 1
            go(r - 1, c, used + 1);
        }
        go(r, c + 1, used + 1);
    }
    
    int calc(V_s board) {
        weight.resize(2, V_i(board[0].size(), 1000000));
        go(0, 0, 1);
        go(1, 0, 1);
        return min(weight[0].last(), weight[1].last());
    }
};


// 1
struct GreaterGameDiv2 {
    
    int calc(V_i snuke, V_i sothe) {
        int pp = 0;
        for (int i = 0; i < snuke.size(); ++i) {
            if (snuke[i] > sothe[i]) ++pp; 
        }
        return pp;
    }

};



