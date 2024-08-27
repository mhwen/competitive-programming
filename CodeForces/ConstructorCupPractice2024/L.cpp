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
	vector<ll> twoPows(1000);
	twoPows[0] = 1;
	for(int i = 1; i < (int)twoPows.size(); i++) {
		twoPows[i] = twoPows[i-1]*2%MOD;
	}
	int n;
	cin >> n;
	vector dp(n+1, vector(n+1, vector<ll>(n+1)));
	dp[1][0][1] = 1;
	for(int sz = 1; sz < n; sz++) {
		for(int left = 0; left <= n; left++) {
			for(int right = 0; right <= n; right++) {
				if(right < n) {
					dp[sz+1][left][right+1] += dp[sz][left][right]*left%MOD*twoPows[right]%MOD;
					dp[sz+1][left][right+1] %= MOD;
				}
				
				dp[sz+1][right][1] += dp[sz][left][right]*right%MOD;
				dp[sz+1][right][1] %= MOD;
			}
		}
	}
	ll ans = 0;
	for(int left = 0; left <= n; left++) {
		for(int right = 0; right <= n; right++) {
			ans += dp[n][left][right];
			ans %= MOD;
		}
	}
	cout << ans << "\n";
}