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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
	ll p = a;
	ll res = 1;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b /= 2;
	}
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> fact(2e5);
	vector<ll> invFact(2e5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	auto choose = [&](ll a, ll b) {
		if(b > a || a < 0 || b < 0)
			return 0LL;
		return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
	};
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		ll ans = 0;
		for(int i = 1; i <= 2*n+1; i++) {
			for(int s = 0; s <= n; s++) {
				int leftTake = (i-1-s);
				int rightTake = s-leftTake;
				ans += i*choose(min(n, i-1), leftTake)%MOD*choose(max(0, n-i), rightTake)%MOD;
				ans %= MOD;
			}
		}
		cout << ans << "\n";
	}
}