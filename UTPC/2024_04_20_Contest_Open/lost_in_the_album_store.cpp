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
constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<ll>> grid(n, vector<ll>(m));
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++)
			cin >> grid[r][c];
	}
	vector<vector<ll>> up(n, vector<ll>(m));
	vector<vector<ll>> left(n, vector<ll>(m));
	for(int r = 0; r < n; r++) {
		for(int c = 1; c < m; c++) {
			left[r][c] = left[r][c-1]+grid[r][c-1];
		}
	}
	for(int c = 0; c < m; c++) {
		for(int r = 1; r < n; r++) {
			up[r][c] = up[r-1][c]+grid[r-1][c];
		}
	}
	vector<vector<ll>> dp(n, vector<ll>(m, INF));
	dp[n-1][m-1] = 0;
	for(int r = n-1; r >= 0; r--) {
		for(int c = m-1; c >= 0; c--) {
			if(c < m-1)
				dp[r][c] = min(dp[r][c], left[r][c]*left[r][c]+dp[r][c+1]);
			if(r < n-1)
				dp[r][c] = min(dp[r][c], up[r][c]*up[r][c]+dp[r+1][c]);
		}
	}
	cout << dp[0][0] << "\n";
}