#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		return res*a%MOD;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<vector<ll>> dp(n+1, vector<ll>(k));
	ll ans = 0;
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		dp[i][0] += dp[i-1][k-1];
		ans += dp[i-1][k-1]*pow(k, n-i)%MOD;
		ans %= MOD;

		for(int j = 1; j < k; j++) {
			dp[i][j] += dp[i-1][j-1]*(k-j+1)%MOD;
			dp[i][j] %= MOD;
		}
		ll sum = 0;
		for(int j = k-1; j > 0; j--) {
			sum += dp[i-1][j];
			dp[i][j] += sum;
			dp[i][j] %= MOD;
		}
		
	}
	
	cout << ans << "\n";
	
}