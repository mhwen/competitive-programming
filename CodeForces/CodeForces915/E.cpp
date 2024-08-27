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
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2)
		res = res*a%MOD;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	map<ll, pair<ll, ll>> seen;
	seen[1] = {1, 0};
	while(t-->0) {
		ll n;
		cin >> n;
		
		function<pair<ll, ll>(ll)> calc = [&](ll rem) {
			if(seen.count(rem)) {
				return seen[rem];
			}
			ll leftAmount = (rem+1)/2;
			ll rightAmount = rem/2;
			auto left = calc(leftAmount);
			auto right = calc(rightAmount);
			ll val1 = (pow(2, leftAmount)-1+MOD)%MOD;
			ll val2 = (pow(2, rightAmount)-1+MOD)%MOD;
			ll myWays = val1*val2%MOD;
			ll myFactor = ((myWays+left.first*2%MOD)%MOD+right.first*2)%MOD;
			ll myExtra = ((left.second+right.second)%MOD+right.first)%MOD;
			seen[rem] = {myFactor, myExtra};
			return pair<ll, ll>{myFactor, myExtra};
		};
		auto ans = calc(n);
		cout << (ans.first+ans.second)%MOD << "\n";
	}
	
}