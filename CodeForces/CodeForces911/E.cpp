#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		vector<vector<int>> adj(n);
		vector<vector<int>> adj_rev(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a].push_back(b);
			adj_rev[b].push_back(a);
		}
		vector<bool> used(n);
		vector<int> order, component;
		function<void(int)> dfs1 = [&](int v) {
			used[v] = true;
			for(int next : adj[v]) {
				if(!used[next])
					dfs1(next);
			}
			order.push_back(v);
		};
		
		function<void(int)> dfs2 = [&](int v) {
			used[v] = true;
			component.push_back(v);
			for(int next : adj_rev[v]) {
				if(!used[next])
					dfs2(next);
			}
		};
		
		for(int i = 0; i < n; i++) {
			if(!used[i])
				dfs1(i);
		}
		for(int i = 0; i < n; i++)
			used[i] = false;
		
		reverse(order.begin(), order.end());
		
		vector<int> roots(n);
		vector<int> sizes(n);
		vector<int> root_nodes;
		vector<ll> cost(n);
		vector<vector<int>> adj_scc(n);
		vector<vector<int>> rev_adj_scc(n);
		for(int v : order) {
			if(!used[v]) {
				dfs2(v);
				int root = component.front();
				sizes[root] = (int)component.size();
				for(int u : component) {
					roots[u] = root;
					cost[root] += nums[u];
				}
				root_nodes.push_back(root);
				
				component.clear();
			}
		}
		vector<int> degree(n);
		for (int v = 0; v < n; v++) {
		    for (auto u : adj[v]) {
		        int root_v = roots[v],
		            root_u = roots[u];
		
		        if (root_u != root_v) {
		        	adj_scc[root_v].push_back(root_u);
		        	rev_adj_scc[root_u].push_back(root_v);
		        }
		    }
		}
		queue<int> q;
		for(int i = 0; i < (int)root_nodes.size(); i++) {
			degree[root_nodes[i]] = (int)adj_scc[root_nodes[i]].size();
			if(degree[root_nodes[i]] == 0)
				q.push(root_nodes[i]);
		}
		vector<pair<int, ll>> path(n);
		pair<int, ll> best = {0, 0};
		while(!q.empty()) {
			int curr = q.front();
			q.pop();
			pair<int, ll> newPath = {path[curr].first+sizes[curr], path[curr].second+cost[curr]};
			if(newPath.first > best.first) {
				best = newPath;
			} 
			else if(newPath.first == best.first) {
				best.second = min(best.second, newPath.second);
			}
			for(int next : rev_adj_scc[curr]) {
				if(newPath.first > path[next].first) {
					path[next] = newPath;
				}
				else if(newPath.first == path[next].first) {
					path[next].second = min(path[next].second, newPath.second);
				}
				degree[next]--;
				if(degree[next] == 0)
					q.push(next);
			}
		}
		cout << best.first << " " << best.second << "\n";
	}
}