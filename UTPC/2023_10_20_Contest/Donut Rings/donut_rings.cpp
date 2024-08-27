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
	vector<ll> radii(n);
	for(int i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		donuts[i] = {r, l};
		radii[i] = r;
	}
	sort(donuts.begin(), donuts.end());
	sort(radii.begin(), radii.end());
	vector<ll> dp(n);
	ll ans = -INF;
	for(int i = 0; i < n; i++) {
		ll holeRadius = donuts[i].second;
		ll outerRadius = donuts[i].first;
		ll area = calcArea(holeRadius, outerRadius);
		dp[i] = area;
		if(i > 0)
			dp[i] = max(dp[i], dp[i-1]);
		auto it = upper_bound(radii.begin(), radii.end(), holeRadius);
		if(it != radii.begin()) {
			it--;
			int index = (int)(it-radii.begin());
			dp[i] = max(dp[i], area+dp[index]);
		}
		ans = max(ans, dp[i]-(radii[i]*radii[i]-dp[i]));
	}
	cout << ans << "\n";
}