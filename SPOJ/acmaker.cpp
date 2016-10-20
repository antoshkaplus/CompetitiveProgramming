


// i - index in phrase
// j - index in abbr
// u - took letter from current word
// function returns 
int solve(int i, int j, int u) {
	if (t[i][j][u] != UNKNOWN) {
		return t[i][j][u]; 
	}
	
	int r = 0;
	if (i == p.size()) {
		if (u && j == a.size()) r = 1;
		
	} else {
		
		if (t[i] == ' ') {
			if (u) r = solve(i+1, j, 0);
			
		} else {
			
			if (j < a.size() && t[i] == a[j]) {
				r += solve(i+1, j+1, 1);
			}
			
			r += solve(i+1, j, u);
		}
	}
 	return t[i][j][u] = r;
}

solve(0, 0, 0);
