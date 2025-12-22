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
	vector<int> color(n);
	vector<map<int, ll>> cnts(n);
	map<int, ll> total;
	for(int i = 0; i < n; i++) {
		cin >> color[i];
		total[color[i]]++;
	}
	vector<ll> ans(n-1);
	vector<ll> dp(n);
	vector<vector<pair<int, int>>> con(n);

	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back({b, i});
		con[b].push_back({a, i});
	}
	function<void(int, int)> dfs = [&](int curr, int prevEdge) {
		for(auto [next, e] : con[curr]) {
			if(e == prevEdge)
				continue;
			dfs(next, e);
			dp[curr] += dp[next];
			if(sz(cnts[next]) > sz(cnts[curr]))
				swap(cnts[next], cnts[curr]);
			for(auto& [c, cnt] : cnts[next]) {
				dp[curr] -= cnts[curr][c]*cnt*2;
				cnts[curr][c] += cnt;
			}
		}
	
		ll below = cnts[curr][color[curr]];
		ll above = total[color[curr]]-below-1;
		cnts[curr][color[curr]]++;
		dp[curr] += above-below;
		if(prevEdge != -1)
			ans[prevEdge] = dp[curr];
	};
	dfs(0, -1);
	for(ll l : ans)
		cout << l << "\n";
}