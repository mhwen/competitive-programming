#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> bad(n+1, vector<bool>(m));
	for(int r = 1; r <= n; r++) {
		for(int c = 0; c < m; c++) {
			char ch;
			cin >> ch;
			if(ch == '#')
				bad[r][c] = true;
		}
	}
	vector<vector<ll>> dp(n+1, vector<ll>(m, -INF));
	fill(dp[0].begin(), dp[0].end(), 0);
	for(int r = 1; r <= n; r++) {
		int prevC = -1;
		ll prevBest = -INF;
		for(int c = 0; c < m; c++) {
			prevBest++;
			if(bad[r][c]) {
				prevC = c;
				prevBest = -INF;
				continue;
			}
			if(!bad[r-1][c]) {
				dp[r][c] = max(dp[r][c], dp[r-1][c]+c-prevC);
				prevBest = max(prevBest, dp[r-1][c]+1);
			}
			dp[r][c] = max(dp[r][c], prevBest);
			
		}
		prevC = m, prevBest = -INF;
		for(int c = m-1; c >= 0; c--) {
			prevBest++;
			if(bad[r][c]) {
				prevC = c;
				prevBest = -INF;
				continue;
			}
			if(!bad[r-1][c]) {
				dp[r][c] = max(dp[r][c], dp[r-1][c]+prevC-c);
				prevBest = max(prevBest, dp[r-1][c]+1);
			}
			dp[r][c] = max(dp[r][c], prevBest);
			
		}
	}
	ll ans = -1;
	for(int i = 0; i < m; i++) {
		ans = max(ans, dp[n][i]);
	}
	// for(int i = 0; i <= n; i++) {
		// for(int j = 0; j < m; j++) {
			// cout << dp[i][j] << " ";
		// }
		// cout << endl;
	// }
	cout << ans << "\n";
}