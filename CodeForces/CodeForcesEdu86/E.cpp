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
	ll res = 1;
	ll p = a;
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
	ll n, k;
	cin >> n >> k;
	vector<ll> fact(n+5);
	vector<ll> invFact(n+5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	auto choose = [&](ll a, ll b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	if(k >= n)
		cout << 0 << "\n";
	else if(k == 0)
		cout << fact[n] << "\n";
	else {
		ll open = n-k;
		ll ways = bpow(open, n)%MOD;
		ll gaps = 0;
		for(ll i = 1; i < open; i++) {
			if(i%2==1)
				gaps = (gaps+choose(open, i)*bpow(open-i, n)%MOD)%MOD;
			else
				gaps = (gaps-choose(open, i)*bpow(open-i, n)%MOD+MOD)%MOD;
		}
		ways = (ways-gaps+MOD)%MOD;
		cout << choose(n, open)*ways*2%MOD << "\n";
	}
}