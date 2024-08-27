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

ll pow(ll a, ll b) {
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2)
		res = res*a%MOD;
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	vector<ll> fact(2e6+1);
	vector<ll> invFact(2e6+1);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < (int)fact.size(); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	function<ll(ll, ll)> choose = [&](ll a, ll b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k, v;
		cin >> n >> k >> v;
		ll ans = 0;
		for(int i = 1; i < v; i++) {
			ans += choose(n+k-1, k+i)*fact[i-1]%MOD*fact[n-i-1]%MOD;
			ans %= MOD;
		}
		ans += choose(n+k-1, k+v-1)*fact[v-1]%MOD*fact[n-v]%MOD;
		ans %= MOD;
		cout << ans << "\n";
	}
}