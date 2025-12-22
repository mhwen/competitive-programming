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
typedef int ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<ll>> Grid(n+2, vector<ll>(n+2));
	for(int i = 0; i < m; i++) {
		int r, c;
		cin >> r >> c;
		Grid[r][c] = 1;
	}
	
	auto rotL = [&](const vector<vector<ll>>& grid) {
		vector<vector<ll>> res(n+2, vector<ll>(n+2));
		for(int r = 0; r <= n+1; r++) {
			for(int c = 0; c <= n+1; c++) {
				res[r][c] = grid[c][n+1-r];
			}
		}
		return res;
	};
	
	auto rotR = [&](const vector<vector<ll>>& grid) {
		return rotL(rotL(rotL(grid)));
	};
	
	auto solve = [&](const vector<vector<ll>>& grid) {
		vector<int> leastR(n+2, INF);
		vector<int> leastC(n+2, INF);
		for(int r = 1; r <= n; r++) {
			for(int c = n; c >= 1; c--) {
				if(grid[r][c])
					leastR[r] = c;
			}
		}
		for(int c = 1; c <= n; c++) {
			for(int r = n; r >= 1; r--) {
				if(grid[r][c])
					leastC[c] = r;
			}
		}
		vector<vector<int>> latestR(n+2, vector<int>(n+2, -1));
		vector<vector<int>> latestC(n+2, vector<int>(n+2, -1));
		for(int r = 1; r <= n+1; r++) {
			for(int c = 1; c <= n+1; c++) {
				if(leastC[c] <= r)
					latestC[r][c] = c;
				else
					latestC[r][c] = latestC[r][c-1];
				if(leastR[r] <= c)
					latestR[r][c] = r;
				else
					latestR[r][c] = latestR[r-1][c];
			}
		}
		vector<vector<ll>> dp(n+2, vector<ll>(n+2, INF));
		for(int i = 0; i <= n+1; i++) {
			dp[0][i] = 0;
			dp[i][0] = 0;
		}
		for(int r = 1; r <= n+1; r++) {
			for(int c = 1; c <= n+1; c++) {
				if(latestC[r][c] == -1)
					dp[r][c] = 0;
				else {
					int latC = latestC[r][c];
					int latR = latestR[r][c];
					dp[r][c] = min(dp[r][latC-1]+r+1, dp[latR-1][c]+c+1);
				}
			}
		}
		return dp;
	};
	
	auto topLeft = solve(Grid);
	auto topRight = rotR(solve(rotL(Grid)));
	auto bottomLeft = rotL(solve(rotR(Grid)));
	auto bottomRight = rotL(rotL(solve(rotR(rotR(Grid)))));
	
	vector<vector<ll>> counts(n+2, vector<ll>(n+2));
	for(int r = 1; r <= n+1; r++) {
		for(int c = 1; c <= n+1; c++) {
			counts[r][c] = Grid[r][c]+counts[r-1][c]+counts[r][c-1]-counts[r-1][c-1];
		}
	}
	
	ll ans = INF;
	//Do main split
	for(int r = 1; r <= n; r++) {
		ll top = INF, bot = INF;
		for(int c = 1; c <= n; c++) {
			bot = min(bot, bottomLeft[r+1][c-1]+bottomRight[r+1][c+1]+n+1-r);
			top = min(top, topLeft[r-1][c-1]+topRight[r-1][c+1]+r);
		}
		if(counts[n][n]-counts[r][n] == 0)
			bot = 0;
		if(counts[r-1][n] == 0)
			top = 0;
		ans = min(ans, bot+top);
	}
	for(int c = 1; c <= n; c++) {
		ll left = INF, right = INF;
		for(int r = 1; r <= n; r++) {
			left = min(left, topLeft[r-1][c-1]+bottomLeft[r+1][c-1]+c);
			right = min(right, topRight[r-1][c+1]+bottomRight[r+1][c+1]+n+1-c);
		}
		if(counts[n][c-1] == 0)
			left = 0;
		if(counts[n][n]-counts[n][c] == 0)
			right = 0;
		ans = min(ans, left+right);
	}
	cout << ans+n+1 << "\n";
	

}