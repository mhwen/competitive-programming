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
	int n, m, x, y;
	cin >> n >> m >> x >> y;
	vector<string> grid(n);
	for(int i = 0; i < n ;i++)
		cin >> grid[i];
	x--; y--;
	vector vis(n, vector<bool>(m));
	vis[x][y] = true;
	string t;
	cin >> t;
	for(char c : t) {
		if(c == 'U' && grid[x-1][y] != '#')
			x--;
		if(c == 'D' && grid[x+1][y] != '#')
			x++;
		if(c == 'L' && grid[x][y-1] != '#')
			y--;
		if(c == 'R' && grid[x][y+1] != '#')
			y++;
		vis[x][y] = true;
	}
	int ans = 0;
	for(int r = 0; r < n; r++)
		for(int c = 0; c < m; c++)
			if(vis[r][c] && grid[r][c] == '@')
				ans++;
	cout << x+1 << " " << y+1 << " " << ans << "\n";
}