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
	int n, m, f, start, end;
	cin >> n >> m >> f >> start >> end;
	vector<vector<pair<int, ll>>> roads(n);
	vector<vector<int>> flights(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		roads[a].emplace_back(b, c);
		roads[b].emplace_back(a, c);
	}
	for(int i = 0; i < f; i++) {
		int a, b;
		cin >> a >> b;
		flights[a].push_back(b);
	}
	priority_queue<pair<ll, pair<int, int>>> q;
	vector<vector<ll>> vis(2, vector<ll>(n, INF));
	q.push({0, {start, 0}});
	while(!q.empty()) {
		auto c = q.top();
		q.pop();
		ll dist = -c.first;
		int curr = c.second.first;
		int flown = c.second.second;
		if(vis[flown][curr] != INF)
			continue;
		vis[flown][curr] = dist;
		for(auto& [next, cost] : roads[curr]) {
			if(vis[flown][next] != INF)
				continue;
			q.push({-dist-cost, {next, flown}});
		}
		if(!flown) {
			for(auto next : flights[curr]) {
				if(vis[1][next] != INF)
					continue;
				q.push({-dist, {next, 1}});
			}
		}
	}
	cout << min(vis[0][end], vis[1][end]) << "\n";
}