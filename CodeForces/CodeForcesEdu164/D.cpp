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
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> val(n);
	for(int i = 0; i < n; i++) {
		cin >> val[i];
	}
	vector<ll> dp(5001, 0);
	dp[0] = 1;
	for(int i = 0; i < n; i++) {
		for(int j = 5000; j-val[i] >= 0; j--) {
			dp[j] += dp[j-val[i]];
			dp[j] %= MOD;
		}
	}

	ll ans = 0;
	for(int i = 0; i <= 5000; i++) {
		ans += (i+1)/2*dp[i]%MOD;
		ans %= MOD;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < val[i]; j++) {
			ans -= (val[i]+j+1)/2*dp[j]%MOD;
			ans += dp[j]*val[i]%MOD;
			ans += MOD;
			ans %= MOD;
		}
	}
	cout << ans << "\n";
}