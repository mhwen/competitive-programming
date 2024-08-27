#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;


void dfs(int curr, int prev, int d, vector<bool>& vis, vector<vector<pair<int,int>>>& con, vector<pair<int,int>>& extra, vector<int>& par, vector<int>& color, vector<int>& depth) {
	vis[curr] = true;
	depth[curr] = d;
	for(auto edge : con[curr]) {
		int next = edge.first;
		int id = edge.second;
		if(next == prev)
			continue;
		if(vis[next]) {
			extra.push_back(edge);
			color[id] = 1;
			continue;
		}
		par[next] = id;
		color[id] = 0;
		dfs(next, curr, d+1, vis, con, extra, par, color, depth);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<pair<int,int>>> con(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			con[a].push_back({b, i});
			con[b].push_back({a, i});
		}
		vector<pair<int, int>> extra;
		vector<int> par(n);
		vector<int> color(m, -1);
		vector<bool> vis(n);
		vector<int> depth(n);
		dfs(0, -1, 0, vis, con, extra, par, color, depth);
		// for(auto edge : extra)
			// cout << edge.first+1 << " " << edge.second << endl;

		set<int> cycle;
		for(auto edge : extra)
			cycle.insert(edge.first);
		if(extra.size() == 6 && cycle.size() == 3) {
			int max_depth = 0;
			
			for(auto edge : extra) {
				max_depth = max()
				color[edge.second] = 0;
			}
			sort(depths.begin(), depths.end());
			for(auto edge : extra) {
				if(depth[edge.first] == depths[2]) {
					color[par[edge.first]] = 1;
					color[edge.second] = 1;
				}
			}
		}
		for(int i : color)
			cout << i;
		cout << "\n";
	}
}