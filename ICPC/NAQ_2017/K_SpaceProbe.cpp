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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	ll l, r;
	cin >> n >> k >> l >> r;
	vector<ll> m(n);
	for(int i = 0; i < n; i++) {
		cin >> m[i];
	}
	vector<pair<ll, ll>> bad(k);
	for(int i = 0; i < k; i++) {
		cin >> bad[i].first >> bad[i].second;
	}
	vector<pair<ll, int>> events;
	auto intersect = [&](ll a, ll b, ll c, ll d) {
		return pair{max(a, c), min(b, d)};
	};
	ll total = r-l;
	for(ll& offset : m) {
		vector<pair<ll, ll>> ints;
		for(auto& [bl, br] : bad) {
			ll L = l+offset;
			ll R = r+offset;
			auto inter = intersect(L, R, bl, br);
			if(inter.second-inter.first >= total) {
				cout << 0 << "\n";
				return 0;
			}
			if(inter.first <= inter.second) {
				events.emplace_back(inter.first-offset, 1);
				events.emplace_back(inter.second-offset, -1);
			}
		}
	}
	sort(all(events));
	ll badCount = 0;
	ll active = 0;
	ll prev = 0;
	for(int i = 0; i < sz(events); i++) {
		ll p = events[i].first;
		int delta = events[i].second;
		if(active > 0 && (i > 0 && events[i].first != events[i-1].first))
			badCount+=p-prev;
		prev = p;
		active += delta;
	}
	cout << fixed << setprecision(20) << 1-(ld)badCount/total << "\n";
}