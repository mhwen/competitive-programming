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

constexpr ll MOD = 998244353;

ll pow(ll a, ll b) {
	ll res = 1;
	ll p = a;
	while(b > 0) {
		if(b%2)
			res = res*p%MOD;
		p = p*p%MOD;
		b/=2;
	}
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<ll> fact(5e5+1);
	vector<ll> invFact(5e5+1);
	fact[0] = fact[1] = 1;
	invFact[0] = invFact[1] = 1;
	for(int i = 2; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](int a, int b) {
		if(b > a)
			return 0LL;
		return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
	};
	
	int n, k;
	cin >> n >> k;
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		int rem = n/i-1;
		ans += choose(rem, k-1);
		ans %= MOD;
	}
	cout << ans << "\n";
}