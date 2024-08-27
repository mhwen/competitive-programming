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
	int n;
	cin >> n;
	vector dp(n+1, vector(5, vector<ll>(13)));
	dp[0][0][0] = 1;
	ll ans = 0;
	for(int len = 1; len <= n; len++) {
		for(int aces = 0; aces <= 4; aces++) {
			for(int card = 0; card < 13; card++) {
				if(card == 0) {
					if(aces == 0)
						continue;
					for(int prev = 0; prev < 13; prev++) {
						dp[len][aces][card] += dp[len-1][aces-1][prev];
						dp[len][aces][card] %= MOD;
					}
				}
				else {
					for(int prev = 0; prev < card; prev++) {
						dp[len][aces][card] += dp[len-1][aces][prev];
						dp[len][aces][card] %= MOD;
					}
				}
				if(len == n) {
					ans += dp[len][aces][card];
					ans %= MOD;
				}
			}
		}
	}
	cout << ans << "\n";
	
}