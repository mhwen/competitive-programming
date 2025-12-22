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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<string> grid(n);
		for(int r = 0; r < n; r++)
			cin >> grid[r];
		vector<vector<int>> vis(n, vector<int>(m));
		auto inside = [&](int r, int c) {
			return r >= 0 && r < n && c >=0 && c < m;
		};
		function<int(int, int)> go = [&](int r, int c) {
			if(!inside(r, c))
				return 2;
			if(grid[r][c] == '?')
				return 1;
			if(vis[r][c] != 0)
				return vis[r][c];
			vis[r][c] = 1;
			if(grid[r][c] == 'L')
				vis[r][c] = go(r, c-1);
			else if(grid[r][c] == 'R')
				vis[r][c] = go(r, c+1);
			else if(grid[r][c] == 'D')
				vis[r][c] = go(r+1, c);
			else
				vis[r][c] = go(r-1, c);
			return vis[r][c];
		};
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(grid[r][c] != '?' && vis[r][c] == 0)
					go(r, c);
			}
		}
		auto check = [&](int r, int c) {
			if(!inside(r,c))
				return false;
			if(vis[r][c] == 2)
				return false;
			return true;
		};
		auto stuck = [&](int r, int c) {
			return check(r-1,c)|check(r+1,c)|check(r,c+1)|check(r,c-1);
		};
		int ans = 0;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				if(vis[r][c] == 1 || (grid[r][c] == '?' && stuck(r, c)))
					ans++;
			}
		}
		cout << ans << "\n";
	}
}