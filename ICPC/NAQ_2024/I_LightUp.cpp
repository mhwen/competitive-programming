#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
		cin >> grid[i];
	bool bad = false;
	vector<vector<bool>> seen(n, vector<bool>(n));
	auto outside = [&](int newR, int newC) {
		return newR < 0 || newR >= n || newC < 0 || newC >= n;
	};
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(grid[r][c] >= '0' && grid[r][c] <= '4') {
				int needed = grid[r][c]-'0';
				for(int d = 0; d < 4; d++) {
					int newR = r+dr[d];
					int newC = c+dc[d];
					if(outside(newR, newC))
						continue;
					if(grid[newR][newC] == '?')
						needed--;
				}
				if(needed != 0)
					bad = true;
			}
			if(grid[r][c] == '?') {
				for(int d = 0; d < 4; d++) {
					int newR = r+dr[d];
					int newC = c+dc[d];
					while(!outside(newR, newC) && grid[newR][newC] == '.') {
						seen[newR][newC] = true;
						newR += dr[d];
						newC += dc[d];
					}
					if(!outside(newR, newC) && grid[newR][newC] == '?')
						bad = true;
				}
			}
		}
	}
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(grid[r][c] == '.' && !seen[r][c])
				bad = true;
		}
	}
	if(bad)
		cout << 0 << "\n";
	else
		cout << 1 << "\n";
	
}