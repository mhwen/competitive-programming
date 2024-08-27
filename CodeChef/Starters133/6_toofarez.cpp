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
constexpr ll MOD = 998244353;

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<ll> fact(5e5+5);
	vector<ll> invFact(5e5+5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](int a, int b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		ll res = 0;
		for(int i = 1; i <= min(n, m); i++) {
			ll ways = choose(m, i);
			ll middle = n/i;
			ll extra = n%i;
			ways = ways*pow(fact[i], middle)%MOD;
			ways = ways*fact[i]%MOD*invFact[i-extra]%MOD;
			res += ways;
			res %= MOD;
		}
		cout << res << "\n";
	}
}