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


using namespace std;


int STATE_MAX = 1 << 10;
int t[H_MAX][W_MAX][STATE_MAX];
int g[H_MAX+2][W_MAX+2];

int WALL = 'x';
int DIRTY = '*';
int ROBOT = 'o';
int CLEAN = '.';

struct Item {
	// state and moves come from previous entry
	int h, w, state, moves;
	
	Item(int h, int w, int state, int moves)
		: h(h), w(w), state(state), moves(moves) {}
};

int set(int cur, int index) {
	return cur | (1 << index);	
}

const int[] dh = {-1, 0, 1, 0};
const int[] dw = { 0,-1, 0, 1};

int N;
int end_state;

vector<string> board;

int robot_r;
int robot_c;

void init() {
	for (int r = 0; r <= H+1; ++r) {
		g[r][0] = g[r][W+1] = WALL;
	}
	for (int c = 0; c <= W+1; ++c) {
		g[0][c] = g[H+1][c] = WALL;
	}
	N = 0;
	for (int r = 1; r <= H; ++r) {
		for (int c = 1; c <= W; ++c) {
			auto v = t[r-1][c-1];
			fill_n(v, set(0, N));
			g[r][c] = board[r-1][c-1];
			if (g[r][c] == DIRTY) {
				g[r][c] = 'A' + N++;
			}
			if (g[r][c] == ROBOT) {
				g[r][c] = EMPTY;
				v[0] = 0;
				robot_r = r;
				robot_c = c;
			}
		}
	}
	
	end_state = 0;
	for (int i = 0; i < N; ++i) {
		end_state = set(end_state, i); 
	} 
}


// minimum moves to get over everything
int solve() {
	queue<Item> q;
	q.emplace(robot_r, robot_c, 0, 0);
	while (!q.empty()) {
		auto p = q.top();
		q.pop();
		auto val = g[p.h][p.w];
		if (val == WALL) {
			continue;
		} 
		
		++p.moves;
		// use letters 
		if (val != CLEAN) {
			auto index = val-'A';
			p.state = set(p.state, index);
		}
		if (p.state == end_state) return p.moves;
		
		if (t[p.h-1][p.w-1][p.state] != -1) {
			continue;
		}
		
		t[p.h-1][p.w-1][p.state] = p.moves;
		for (auto i = 0; i < 4; ++i) {
			int h = p.h + dh[i];
			int w = p.w + dw[i];
			q.emplace(h, w, p.state, p.moves);
		}
	}
	return -1;
}


int main(int argc, char **argv) {
	std::ios_base::sync_with_stdio(false);
	for (;;) {
		cin >> W >> H;
		if (W == 0 && H == 0) {
			break;
		}
		board.resize(H);
		for (auto& b : board) {
			cin >> b;
		}
		init();
		cout << solve() << endl;
	}
}
