#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll INF = 2e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	set<ll> orders;
	vector<ll> batches(n);
	ll total = 0;
	for(int i = 0; i < n; i++) {
		ll a;
		cin >> a;
		orders.insert(a);
	}
	for(int i = 0; i < n; i++) {
		cin >> batches[i];
		total += batches[i];
	}
	if(n == 1) {
		if(*orders.begin() == total) {
			cout << 0 << "\n";
		}
		else {
			cout << -1 << "\n";
		}
	}
	else {
		ll ans = INF;
		for(ll b : batches) {
			auto below = orders.upper_bound(b);
			if(below != orders.begin()) {
				below--;
				ans = min(ans, b-*below);
			}
			auto above = orders.lower_bound(b);
			if(above != orders.end() && *above <= total) {
				ans = min(ans, *above-b);
			}
		}
		if(ans == INF)
			cout << -1 << "\n";
		else
			cout << ans << "\n";
	}
	
}