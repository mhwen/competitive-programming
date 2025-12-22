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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<ll>> dp(4, vector<ll>(2*n+1, INF));
	dp[0][n] = 0;
	ll mCount = 0;
	for(int i = 0; i < n; i++) {
		ll m, f;
		cin >> m >> f;
		mCount += m;
		vector<vector<ll>> newDp(4, vector<ll>(2*n+1, INF));
		for(int mask = 0; mask < 4; mask++) {
			for(int offset = -n; offset <= n; offset++) {
				int j = offset+n;
				if(dp[mask][j] == INF)
					continue;
				
				if(m > 0) {
					ll remAll = f+m-1;
					int remMask = mask|1;
					newDp[remMask][j] = min(newDp[remMask][j], dp[mask][j]+remAll);
				}
				else {
					ll remAll = f;
					int remMask = mask|1;
					newDp[remMask][j-1] = min(newDp[remMask][j-1], dp[mask][j]+remAll);
				}
				ll move = m;
				ll over = max(0LL, offset+move-n);
				int moveMask = mask|2;
				int newJ = (int)min((ll)2*n, j+move);
				newDp[moveMask][newJ] = min(newDp[moveMask][newJ], dp[mask][j]+move+over);
			}
		}
		dp = newDp;
	}
	ll best = INF;
	for(int i = -n; i <= n; i++) {
		best = min(best, dp[3][i+n]+max(0, i));
	}
	if(mCount == 0)
		best = 0;
	cout << best << "\n";
}