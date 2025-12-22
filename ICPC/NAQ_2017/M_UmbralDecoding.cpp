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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

ll cubeRoot(ll val) {
	ll B = (int)cbrt(val);
	while((B+1)*(B+1)*(B+1) <= val)
		B++;
	return B;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	int k;
	cin >> n >> k;
	map<ll, vector<pair<ll, ll>>> intervals;
	for(int i = 0; i < k; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		ll bound = cubeRoot(c);
		for(ll l = max(0LL, a-bound); l <= min(n, a+bound); l++) {
			ll val = abs(a-l);
			ll range = cubeRoot(c-val*val*val);
			intervals[l].emplace_back(max(0LL, b-range), min(n, b+range));
		}
	}
	ll total = (n+1)*(n+1);
	ll bad = 0;
	for(auto& [_, segs] : intervals) {
		sort(all(segs));
		ll cnt = 0;
		pair<ll, ll> prev{-1, -2};
		for(auto [l, r] : segs) {
			if(l <= prev.second)
				prev.second = max(prev.second, r);
			else {
				cnt += prev.second-prev.first+1;
				prev = {l, r};
			}
		}
		cnt += prev.second-prev.first+1;
		bad += cnt;
	}
	cout << total-bad << "\n";
}