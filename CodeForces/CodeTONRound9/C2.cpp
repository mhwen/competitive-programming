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

ll brute(ll x, ll m) {
	ll cnt = 0;
	for(ll y = 1; y <= m; y++) {
		ll xy = x^y;
		if(xy%x==0 || xy%y==0)
			cnt++;
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll x, m;
		cin >> x >> m;
		auto check = [&](ll val) {
			ll y = x^val;
			return y <= m;
		};
		
		ll ans = 0;
		ll l = 1, r = (ll)2e18/x;
		while(l <= r) {
			ll mid = l+(r-l)/2;
			if(check(mid*x))
				l = mid+1;
			else
				r = mid-1;
		}
		ans += r-1;
		auto bad = [&](ll val) {
			if(val < 0)
				return false;
			ll y = val^x;
			if(y > m || y <= x)
				return true;
			if(val%y!=0 && val%x!=0)
				return true;
			return false;
		};
		auto good = [&](ll val) {
			if(val < 0)
				return false;
			ll y = val^x;
			if(y > m || y <= x)
				return false;
			if(val%y==0 || val%x==0)
				return true;
			return false;
		};
		
		for(ll i = max(2LL, r-10); i <= r; i++) {
			if(bad(x*i))
				ans--;
		}
		for(ll i = r+1; i <= r+10; i++) {
			if(good(x*i))
				ans++;
		}
		for(int y = 1; y <= min(x, m); y++) {
			ll xy = x^y;
			if(xy%x==0 || xy%y==0)
				ans++;
		}
		cout << ans << "\n";
		// if(ans != brute(x, m))
			// cout << x << " " << m << " " << ans << " " << brute(x, m) << endl;
		// assert(ans == brute(x, m));
	}
}