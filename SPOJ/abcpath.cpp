#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;


// boundary letters should be max
// that way easy to skip
Grid<int> length;
Grid<int> letters;

// from current position try to move to every direction
bool Update(Position p) {
	bool changed = false;
	for (auto& s : kDirShirft) {
		auto p_2 = p + s;
		if (letters(p)+1 == letters(p_2) && length(p)+1 > length(p_2)) {
			length(p_2) = length(p)+1;
			changed = true;
		}
	}
	return changed;
}

void InitLetters(vector<string> s) {
	letters = Grid<int>(H+2, W+2, numeric_limits<int>::max());
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			letters(i+1, j+1) = s[i][j];
		}
	}
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
	int test_case = 1;
	for (;;) {
		int H, W;
		cin >> H >> W;
		if (H == 0 && W == 0) {
			break;
		}
		vector<string> s(H);
		// could do usual loop
		for (int i = 0; i < H; ++i) {
			cin >> s[i];
		}
		
		// we should use grid with positions
		length = Grid<int>(H, W, 1);
		for (int k = 0; k < H*W; ++k) {
			bool changed = false;
			for (int r = 1; r <= H; ++r) {
				for (int c = 1; c <= W; ++c) {
					// first check if one more, then check actual scores
					changed = Update(r, c);
				}
			}
			if (!changed) break;
		}
		max_element(length.begin(), )
		cout << "Case " << test_case++ << ": " << length(r, c) << endl;
	}
	
	
	
	int N;
    cin >> N;
    
    int n = sqrt(N);
    int res = 0;
    for (int k = 1; k <= n; ++k) {
        res += N/k - k + 1;
    }
    cout << res << endl;
}
