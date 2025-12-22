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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	ll x, y;
	cin >> n >> m >> x >> y;
	vector<pair<ll, ll>> coords(n);
	for(int i = 0; i < n; i++) {
		cin >> coords[i].first >> coords[i].second;
	}
	map<ll, vector<pair<ll, ll>>> X;
	map<ll, vector<pair<ll, ll>>> Y;
	for(int i = 0; i < m; i++) {
		char d;
		ll c; 
		cin >> d >> c;
		ll newX = x;
		ll newY = y;
		if(d == 'U')
			newY += c;
		if(d == 'D')
			newY -= c;
		if(d == 'L')
			newX -= c;
		if(d == 'R')
			newX += c;
		if(x != newX)
			Y[y].push_back({min(x, newX), max(x, newX)});
		else
			X[x].push_back({min(y, newY), max(y, newY)});
		x = newX;
		y = newY;
	}
	auto fix = [](map<ll, vector<pair<ll, ll>>>& a) {
		for(auto& [_, v] : a) {
			sort(all(v));
			vector<pair<ll, ll>> merged;
			for(auto [l,r] : v) {
				if(merged.empty() || l > merged.back().second)
					merged.push_back({l, r});
				else
					merged.back().second = max(merged.back().second, r);
			}
			v = merged;
		}
	};
	fix(X);
	fix(Y);

	auto check = [](vector<pair<ll, ll>>& a, ll target) {
		auto it = lower_bound(all(a), pair{target+1, target});
		if(it != a.begin()) {
			it--;
			auto [l, r] = *it;
			if(l <= target && target <= r)
				return true;
		}
		return false;
	};
	ll ans = 0;
	for(auto [xx, yy] : coords) {
		if(check(X[xx], yy) || check(Y[yy], xx))
			ans++;
	}
	cout << x << " " << y << " " << ans << "\n";
}