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
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
	ll p = a;
	ll res = 1;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b >>= 1;
	}
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		int x = n-k;
		ll aliceNormal = (x+1)/2;
		ll bobNormal = x/2;
		ll aliceSpecial = (x+2)/2;
		ll bobSpecial = (x+1)/2;
		ll specialSum = 0, normalSum = 0;
		for(int i = 0; i < n; i++) {
			ll num;
			cin >> num;
			if(i < k)
				specialSum += num;
			else
				normalSum += num;
		}
		specialSum %= MOD;
		normalSum %= MOD;
		if(k == n) {
			cout << specialSum << " " << 0 << "\n";
		}
		else {
			ll alice = aliceNormal*inv(x)%MOD*normalSum%MOD +
					aliceSpecial*inv(x+1)%MOD*specialSum%MOD;
			alice %= MOD;
			ll bob = bobNormal*inv(x)%MOD*normalSum%MOD + 
					 bobSpecial*inv(x+1)%MOD*specialSum%MOD;
			bob %= MOD;
			cout << alice << " " << bob << "\n";
					 
		}
	}
}