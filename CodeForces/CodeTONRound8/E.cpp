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
	
	vector<ll> fact(1e6+5);
	vector<ll> invFact(1e6+5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < (int)fact.size(); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](ll a, ll b) -> ll {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int l, n;
		cin >> l >> n;
		int cows = n*2;
		ll totalWays = choose(l, cows)*2%MOD;
		ll badWays = 0;
		ll extraSpace = l-cows;
		for(ll middle = 0; middle*2 <= extraSpace; middle++) {
			ll unused = extraSpace-middle*2;
			ll outerWays = choose(n+unused, unused);
			ll innerWays = choose(n+middle-1, middle);
			// cout << middle << " " << innerWays << " " << outerWays << endl;
			badWays += innerWays*outerWays%MOD;
			badWays %= MOD;
		}
		badWays *= 2;
		badWays %= MOD;
		// cout << totalWays << " " << badWays << endl;
		cout << (totalWays-badWays+MOD)%MOD << "\n";
	}
}