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
	//Sort by outer radius
	sort(donuts.begin(), donuts.end());
	
	vector<ll> dp(n);
	ll ans = -INF;
	
	for(int i = 0; i < n; i++) {
		ll holeRadius = donuts[i].second;
		ll outerRadius = donuts[i].first;
		ll area = calcArea(holeRadius, outerRadius);
		dp[i] = area-holeRadius*holeRadius;
		ans = max(ans, dp[i]);
		//Try all rings that fit inside current donut
		for(int j = 0; j < i; j++) {
			ll ringRadius = donuts[j].first;
			ll emptySpace = calcArea(ringRadius, holeRadius);
			if(ringRadius <= holeRadius) {
				dp[i] = max(dp[i], area-emptySpace+dp[j]);
			}
		}
		ans = max(ans, dp[i]);
	}
	cout << ans << "\n";
}