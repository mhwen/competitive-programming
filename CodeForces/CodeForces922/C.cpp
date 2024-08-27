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

ll solve(ll a, ll b, ll r) {
	ll diff = a-b;
	for(int bit = 61; bit >= 0; bit--) {
		ll val = 1LL<<bit;
		if(val <= r) {
			ll change = (a^val)-(b^val);
			if(abs(change) < abs(diff)) {
				r -= val;
				a ^= val;
				b ^= val;
				diff = a-b;
			}
		}
	}
	return abs(diff);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll a, b, r;
		cin >> a >> b >> r;
		ll r2 = 1;
		while(r2*2 <= r)
			r2 *= 2;
		r2--;
		cout << min(solve(a, b, r), solve(a, b, r2)) << "\n";
	}
}