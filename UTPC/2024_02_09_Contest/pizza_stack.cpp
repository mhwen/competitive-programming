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
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<vector<ll>> dp(n+1, vector<ll>(k+1));
	dp[1][0] = 1;
	for(int i = 2; i <= n; i++) {
		ll window = 0;
		for(int j = 0; j <= k; j++) {
			if(j >= i) {
				window -= dp[i-1][j-i];
				if(window < 0)
					window += MOD;
			}
			window += dp[i-1][j];
			window %= MOD;
			dp[i][j] = window;

		}
	}
	cout << dp[n][k] << "\n";
}