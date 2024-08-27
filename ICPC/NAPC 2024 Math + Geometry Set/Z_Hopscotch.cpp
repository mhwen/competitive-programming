#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
	if(b==0)
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
	int n, x, y;
	cin >> n >> x >> y;
	vector<ll> fact(2*n);
	vector<ll> invFact(2*n);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](int a, int b) -> ll {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	ll ways = 0;
	for(int i = 1; i <= n; i++) {
		int remX = n-x*i;
		int remY = n-y*i;
		if(remX < 0 || remY < 0)
			break;
		ways += choose(remX+i-1, i-1)*choose(remY+i-1, i-1)%MOD;
		ways %= MOD;
	}
	cout << ways << "\n";
}