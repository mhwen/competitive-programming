#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr ll INF = 5e18;

ll calcArea(ll inner, ll outer) {
	return outer*outer-inner*inner;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<pair<ll, ll>> donuts(n);
	for(int i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		donuts[i] = {r, l};
	}
	sort(donuts.begin(), donuts.end());
	ll ans = calcArea(donuts[0].second, donuts[0].first)-calcArea(0, donuts[0].second);
	ll radius = donuts[0].first;
	for(int i = 1; i < n; i++) {
		if(radius <= donuts[i].second) {
			ll area = calcArea(donuts[i].second, donuts[i].first);
			ll space = calcArea(radius, donuts[i].second);
			if(area-space > 0) {
				ans += area-space;
				radius = donuts[i].first;
			}
		}
	}
	cout << ans << "\n";
}