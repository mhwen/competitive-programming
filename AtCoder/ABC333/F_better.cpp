#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
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
	
	vector<ll> fact(5000);
	vector<ll> invFact(5000);
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
	int n;
	cin >> n;
	vector<ll> dp(n);
	dp[0] = 1;
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < i; j++) {
			dp[i] = (dp[i]+choose(i, j)*dp[j]%MOD)%MOD;
		}
		dp[i] = dp[i]*inv(pow(2, i+1)-1+MOD%MOD)%MOD;
	}
	for(int i = 0; i < n; i++) {
		ll chance = 0;
		for(int j = 0; j <= i; j++) {
			chance = (chance+choose(i, j)*dp[n-j-1]%MOD)%MOD;
		}
		chance = chance*inv(pow(2, i))%MOD;
		cout << chance << " ";
	}
	cout << "\n";
}