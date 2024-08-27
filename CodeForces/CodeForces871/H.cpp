#include <iostream>
#include <vector>
#include <bit>

using namespace std;

typedef long long ll;
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<vector<ll>> dp(n+1, vector<ll>(64));
		dp[0][63] = 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 64; j++) {
				dp[i+1][nums[i]&j] += dp[i][j];
				dp[i+1][nums[i]&j] %= MOD;
				dp[i+1][j] += dp[i][j];
				dp[i+1][j] %= MOD;
			}
		}
		ll ans = 0;
		for(unsigned int j = 0; j < 64; j++) {
			if(popcount(j) == k) {
				ans += dp[n][j];
				ans %= MOD;
			}
		}
		if(k == 6)
			ans--;
		cout << ans << "\n";
	}

}