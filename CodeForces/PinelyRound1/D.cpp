#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
constexpr ll MOD = 1e9+7;

vector<ll> fac, invFac;

ll pow(ll a, ll b) {
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res *= a;
	return res%MOD;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

ll choose(int a, int b) {
	if(b > a)
		return 0;
	return fac[a]*invFac[a-b]%MOD*invFac[b]%MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	
	if(k == 0) {
		cout << pow(3, n) << "\n";
		return 0;
	}
	
	fac = vector<ll>(n+1);
	fac[0] = 1;
	for(int i = 1; i < (int)fac.size(); i++) {
		fac[i] = fac[i-1]*i%MOD;
	}
	invFac = vector<ll>(n+1);
	for(int i = 0; i < (int)fac.size(); i++) {
		invFac[i] = inv(fac[i]);
	}
	
	ll sum = 0;
	for(int q = 1; q <= n; q++) {
		ll val = pow(3, n-q)*choose(k-1, (q+1)/2-1)%MOD*choose(n-k, (q+2)/2-1)%MOD;
		sum = (sum+val)%MOD;
	}
	cout << sum%MOD;
	
}