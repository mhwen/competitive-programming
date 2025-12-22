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
	int n;
	cin >> n;
	pair<ll, ll> me;
	cin >> me.first >> me.second;
	pair<ll, ll> ans{1e7, 1e7};
	ll best = 1e18;
	auto dist = [&](pair<ll, ll> them) {
		ll dx = me.first-them.first;
		ll dy = me.second-them.second;
		return dx*dx+dy*dy;
	};
	for(int i = 0; i < n; i++) {
		pair<ll, ll> them;
		cin >> them.first >> them.second;
		ll d = dist(them);
		if(d < best) {
			best = d;
			ans = them;
		}
		else if(d == best)
			ans = min(ans, them);
	}
	cout << ans.first << " " << ans.second << "\n";
}
