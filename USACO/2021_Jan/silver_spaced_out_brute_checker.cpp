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

void check(int mask, int n) {
	vector<vector<int>> grid(n, vector<int>(n));
	int id = 0;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(mask & (1<<id))
				grid[r][c] = 1;
			id++;
		}
	}
	for(int r = 0; r < n-1; r++) {
		for(int c = 0; c < n-1; c++) {
			if(grid[r][c]+grid[r][c+1]+grid[r+1][c]+grid[r+1][c+1] != 2)
				return;
		}
	}
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			cout << grid[r][c];
		}
		cout << endl;
	}
	cout << endl;
}

void search(int r, int c, int n, vector<vector<int>>& grid) {
	if(c == n) {
		c = 0;
		r++;
	}
	if(r == n) {
		for(int R = 0; R < n; R++) {
			for(int C = 0; C < n; C++) {
				cout << grid[R][C];
			}
			cout << endl;
		}
		cout << endl;
		return;
	}
	bool zeroGood = true;
	if(r > 0 && c > 0) {
		if((grid[r][c]+grid[r-1][c]+grid[r][c-1]+grid[r-1][c-1])%2 == 1)
			zeroGood = false;
	}
	if(zeroGood)
		search(r, c+1, n, grid);
		
	bool oneGood = true;
	grid[r][c] = 1;
	if(r > 0 && c > 0) {
		if((grid[r][c]+grid[r-1][c]+grid[r][c-1]+grid[r-1][c-1])%2 == 1)
			oneGood = false;
	}
	if(oneGood)
		search(r, c+1, n, grid);
	grid[r][c] = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> grid(n, vector<int>(n));
	search(0, 0, n, grid);
}