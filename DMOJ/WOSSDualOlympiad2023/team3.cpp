#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef long long ll;
constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> adj(n);
	vector<vector<pair<int, int>>> r_adj(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].push_back({v, 0});
		r_adj[v].push_back({u, 0});
	}
	for(int i = 0; i < k; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		u--; v--;
		adj[u].push_back({v, c});
		r_adj[v].push_back({u, c});
	}
	vector<vector<pair<int, int>>> distFromStart(n, vector<pair<int, int>>(2, {INF, INF}));
	vector<vector<pair<int, int>>> distFromEnd(n, vector<pair<int, int>>(2, {INF, INF}));

	function<void(int, vector<vector<pair<int, int>>>&, vector<vector<pair<int, int>>>&)> search = [&](int start, vector<vector<pair<int, int>>>& dists, vector<vector<pair<int, int>>>& con) {
		queue<pair<int, pair<int, int>>> q;
		q.push({start, {0, 0}});
		while(!q.empty()) {
			auto cc = q.front();
			q.pop();
			int curr = cc.first;
			int dist = cc.second.first;
			int colorUsed = cc.second.second;
			if(dists[curr][1].first != INF)
				continue;
			else if(dists[curr][0].first == INF) {
				dists[curr][0] = {dist, colorUsed};
			}
			else {
				if(dists[curr][0].second == colorUsed)
					continue;
				else
					dists[curr][1] = {dist, colorUsed};
			}
			for(auto next : con[curr]) {
				if(colorUsed != 0 && next.second != 0)
					continue;
				q.push({next.first, {dist+1, colorUsed+next.second}});
			}
		}
	};
	
	search(0, distFromStart, adj);
	search(n-1, distFromEnd, r_adj);
	
	int ans = INF;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 2; j++) {
			for(int h = 0; h < 2; h++) {
				if(distFromStart[i][j].second == distFromEnd[i][h].second && distFromStart[i][j].second != 0)
					continue;
				ans = min(ans, distFromStart[i][j].first+distFromEnd[i][h].first);
			}
		}
	}
	
	if(ans == INF)
		cout << -1 << "\n";
	else
		cout << ans << "\n";
	
	
	
	
}