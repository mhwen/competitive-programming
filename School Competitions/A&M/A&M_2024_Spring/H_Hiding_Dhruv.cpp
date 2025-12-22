#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

const int MAX_SIZE = 1000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int R, C, x;
	cin >> R >> C >> x;
	vector<string> pattern(R);
	for(int r = 0; r < R; r++) {
		cin >> pattern[r];
	}
	
	vector<vector<char>> grid(MAX_SIZE, vector<char>(MAX_SIZE, 'a'));
	
	function<bool(int, int, vector<vector<char>>&)> check = [&](int r, int c, vector<vector<char>>& g) {
		for(int rx = 0; rx < R; rx++) {
			for(int cx = 0; cx < C; cx++) {
				if(g[r+rx][c+cx] == 'a')
					continue;
				if(g[r+rx][c+cx] != pattern[rx][cx])
					return false;
			}
		}
		return true;
	};
	
	function<void(int, int)> apply = [&](int r, int c) {
		for(int rx = 0; rx < R; rx++) {
			for(int cx = 0; cx < C; cx++) {
				grid[r+rx][c+cx] = pattern[rx][cx];
			}
		}
	};
	
	int got = 0;
	for(int r = 0; r+R-1 < MAX_SIZE; r++) {
		for(int c = 0; c+C-1 < MAX_SIZE; c++) {
			if(check(r, c, grid) && got < x) {
				apply(r, c);
				got++;
			}
		}
	}
	
	auto copy = grid;
	for(int r = 0; r < MAX_SIZE; r++) {
		for(int c = 0; c < MAX_SIZE; c++) {
			// cout << grid[r][c];
			if(grid[r][c] == 'a')
				grid[r][c] = '#';
			if(copy[r][c] == 'a')
				copy[r][c] = '.';
		}
		// cout << endl;
	}
	// cout << endl;
	
	int gridCount = 0;
	int copyCount = 0;
	for(int r = 0; r+R-1 < MAX_SIZE; r++) {
		for(int c = 0; c+C-1 < MAX_SIZE; c++) {
			if(check(r, c, grid))
				gridCount++;
			if(check(r, c, copy))
				copyCount++;
		}
	}
	if(gridCount == x) {
		cout << MAX_SIZE << " " << MAX_SIZE << "\n";
		for(int r = 0; r < MAX_SIZE; r++) {
			for(int c = 0; c < MAX_SIZE; c++) {
				cout << grid[r][c];
			}
			cout << "\n";
		}	
	}
	else if(copyCount == x){
		cout << MAX_SIZE << " " << MAX_SIZE << "\n";
		for(int r = 0; r < MAX_SIZE; r++) {
			for(int c = 0; c < MAX_SIZE; c++) {
				cout << copy[r][c];
			}
			cout << "\n";
		}	
	}
	else
		return -1;
		
	
}