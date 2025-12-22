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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> dp(n+1);
		ll p = 0;
		for(int i = n; i >= 3; i--) {
			dp[i] = (p*i+1)%MOD;
			p += dp[i];
			p %= MOD;
		}
		vector<ll> dp2(n+1);
		p = 0;
		for(int i = n; i >= 3; i--) {
			dp2[i] = (p*(i-1)+1)%MOD;
			p += dp[i];
			p %= MOD;
		}
		ll ans = 0;
		for(int i = 3; i <= n; i++) {
			ans += dp2[i];
			ans %= MOD;
		}
		cout << (ans+1)%MOD << endl;
	}
}