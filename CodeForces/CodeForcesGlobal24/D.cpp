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

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	ll MOD;
	cin >> n >> MOD;
	
	auto bpow = [&](ll a, ll b) {
		ll res = 1;
		ll p = a;
		while(b > 0) {
			if(b%2==1)
				res = res*p%MOD;
			p = p*p%MOD;
			b/=2;
		}
		return res;
	};
	
	auto inv = [&](ll a) {
		return bpow(a, MOD-2);
	};
	
	vector<ll> fact(2*n+5);
	vector<ll> invFact(sz(fact));
	invFact[0] = fact[0] = 1;
	for(ll i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	auto choose = [&](ll a, ll b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	
	ll ans = 0;
	for(ll i = 0; i+n/2 <= n-1; i++) {
		ll take = n/2+i;
		ll last = n/2-i;
		ll rem = max(0LL, n-take-2);
		for(ll extra = 0; extra <= rem; extra++) {
			ans += choose(rem, extra)*fact[extra+take-1]%MOD*last%MOD;
			ans %= MOD;
		}
	}
	cout << ans*n%MOD << "\n";
}