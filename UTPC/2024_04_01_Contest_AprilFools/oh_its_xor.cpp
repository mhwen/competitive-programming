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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> adj(n, vector<bool>(n));
	vector<int> vals(n);
	for(int i = 0; i < n; i++)
		cin >> vals[i];
		
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u][v] = true;
		adj[v][u] = true;
	}
	
	set<pair<int, int>> seen;
	set<int> maskSeen;
	queue<pair<int, int>> bfs;
	for(int i = 0; i < n; i++) {
		bfs.push({1<<i, i});
	}
	while(!bfs.empty()) {
		auto curr = bfs.front();
		bfs.pop();
		if(seen.count(curr))
			continue;
		seen.insert(curr);
		int mask = curr.first;
		int node = curr.second;
		maskSeen.insert(mask);
		// for(int bit = 0; bit < n; bit++) {
			// if(mask & (1<<bit))
				// cout << 1;
			// else
				// cout << 0;
		// }
		// cout << endl;
		for(int next = 0; next < n; next++) {
			if(mask & (1<<next))
				continue;
			if(adj[node][next]) {
				bfs.push({mask | (1<<next), next});
			}
		}
	}
	int best = 0;
	for(int mask = 1; mask < (1<<n); mask++) {
		if(maskSeen.count(mask) == 0)
			continue;
		int ans = 0;
		for(int bit = 0; bit < n; bit++) {
			if(mask & (1<<bit))
				ans ^= vals[bit];
		}
		// for(int bit = 0; bit < n; bit++) {
			// if(mask & (1<<bit))
				// cout << 1;
			// else
				// cout << 0;
		// }
		// cout << " " << ans << endl;
		best = max(best, ans);
	}
	cout << best << "\n";
}