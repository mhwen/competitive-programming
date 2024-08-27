#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

bool dfs(int curr, int prev, vector<vector<int>>& con, vector<int>& vis, vector<int>& par) {
	vis[curr] = 1;
	par[curr] = prev;
	for(int next : con[curr]) {
		if(next != prev) {
			if(vis[next]) {
				int cycle = curr;
				while(cycle != next) {
					vis[cycle] = 2;
					cycle = par[cycle];
				}
				vis[cycle] = 2;
				return true;
			}
			else
				if(dfs(next, curr, con, vis, par))
					return true;
		}
	}
	return false;
}

void bfs(int start, vector<vector<int>>& con, vector<int>& dists) {
	queue<pair<int, int>> q;
	vector<bool> vis(con.size());
	q.push({start, 0});
	while(!q.empty()) {
		auto curr = q.front();
		q.pop();
		if(vis[curr.first])
			continue;
		vis[curr.first] = true;
		dists[curr.first] = curr.second;
		for(int next : con[curr.first]) {
			if(!vis[next]) {
				q.push({next, curr.second+1});
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, a, b;
		cin >> n >> a >> b;
		a--;
		b--;
		vector<vector<int>> con(n);
		for(int i = 0; i < n; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
		}
		
		vector<int> cycle(n);
		vector<int> par(n);
		dfs(0, -1, con, cycle, par);
		vector<int> aDist(n);
		vector<int> bDist(n);
		bfs(a, con, aDist);
		bfs(b, con, bDist);
		bool caught = true;
		for(int i = 0; i < n; i++) {
			if(cycle[i] == 2 && bDist[i] < aDist[i]) {
				caught = false;
			}

		}
		if(caught)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}