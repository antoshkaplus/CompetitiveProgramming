

int main() {
	
	auto b = readBoard();
	// so we have a grid
	// have some values that we would want to skipws
	
	g
	// another board is with numbers
	
	// if would have time replace
	auto func = [&](const Position& p, const Position& from) {
		if (b[p] > b[from]) {
			++g[p];
			return Continue;
		}
		return Skip;
	}
	
	
	// you find all 1-s and laaunch BFS from it
	BFS_Prev(b, func);

	// so you end up with a bunch of stupid stuff
	
	
	
}
