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

ll bpow(ll a, ll b) {
	ll p = a;
	ll res = 1;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b/=2;
	}
	return res;
}

ll inv(ll a) {
	return bpow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		ll tot = 1;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			tot = tot*nums[i]%MOD;
		}
		ll gcd = tot;
		ll ans = 0;
		ll prev = 0;
		for(int i = 0; i < n; i++) {
			ll val = tot*inv(nums[i])%MOD;
			ll g = gcd*inv(nums[i])%MOD;
			ll a = (gcd*inv(g)%MOD-1+MOD)%MOD;
			ll b = (val*inv(g)%MOD-1+MOD)%MOD;
			ans = (ans + a*b%MOD*inv(2)%MOD + (gcd-1+MOD)%MOD*prev%MOD)%MOD;
			prev = a*b%MOD*inv(2)%MOD;
			gcd = gcd*inv(nums[i])%MOD;
		}
		cout << ans << "\n";
	}
}