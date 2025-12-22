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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, P;
		cin >> n >> m >> P;
		vector<int> need(n);
		for(int i = 0; i < P; i++) {
			int a;
			cin >> a;
			a--;
			need[a]++;
		}
		vector<pair<ll, pair<int, int>>> edges;
		for(int i = 0; i < m; i++) {
			int u, v;
			ll w;
			cin >> u >> v >> w;
			u--; v--;
			edges.push_back({w, {u, v}});
		}
		sort(all(edges));
		vector<vector<ll>> dp(n, vector<ll>(n+1));
		for(int i = 0; i < n; i++) {
			if(need[i])
				dp[i][0] = INF;
		}
		vector<int> p(n);
		vector<int> s(n, 1);
		iota(all(p), 0);
		function<int(int)> getP = [&](int a) {
			if(a == p[a])
				return a;
			return p[a] = getP(p[a]);
		};
		
		auto merge = [&](int a, int b, ll w) {
			a = getP(a);
			b = getP(b);
			if(a == b)
				return;
			if(s[a] < s[b])
				swap(a, b);
			vector<ll> newDp(n+1, INF);
			if(need[a]+need[b] == 0) {
				fill(all(newDp), 0);
			}
			else {
				int aCurr = 0;
				int bCurr = 0;
				for(int tot = 1; tot <= n; tot++) {
					ll up = dp[a][aCurr+1]+dp[b][bCurr];
					ll down = dp[a][aCurr]+dp[b][bCurr+1];
					if(up <= down) {
						newDp[tot] = min(newDp[tot], up);
						aCurr++;
					}
					else {
						newDp[tot] = min(newDp[tot], down);
						bCurr++;
					}
					newDp[tot] = min(newDp[tot], dp[b][tot]+w*need[a]);
					newDp[tot] = min(newDp[tot], dp[a][tot]+w*need[b]);
				}
			}
			p[b] = a;
			s[a] += s[b];
			need[a] += need[b];
			dp[a] = newDp;
		};
		
		for(auto [w, edge] : edges) {
			int u = edge.first;
			int v = edge.second;
			merge(u, v, w);
		}
		
		int a = getP(0);
		for(int i = 1; i <= n; i++)
			cout << dp[a][i] << " ";
		cout << "\n";
	}
}