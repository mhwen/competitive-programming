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
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> con(n);
	vector<pair<int, int>> edges;
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
		edges.push_back({a, b});
	}
	vector<int> order(n);
	vector<int> depth(n);
	vector<vector<int>> parent(n, vector<int>(60));
	int id = 0;
	function<void(int, int, int)> dfs = [&](int curr, int prev, int dep) {
		order[curr] = id++;
		depth[curr] = dep;
		for(int next : con[curr]) {
			if(next != prev) {
				parent[next][0] = curr;
				dfs(next, curr, dep+1);
			}
		}
	};
	
	dfs(0, 0, 0);
	
	for(int b = 1; b < 60; b++) {
		for(int i = 0; i < n; i++) {
			parent[i][b] = parent[parent[i][b-1]][b-1];
		}
	}
	
	auto lca = [&](int a, int b) {
		if(depth[a] < depth[b])
			swap(a, b);
		int diff = depth[a]-depth[b];
		for(int bit = 0; bit < 60; bit++) {
			if(diff%2)
				a = parent[a][bit];
			diff /= 2;
		}
		if(a == b)
			return a;
		for(int bit = 59; bit >= 0; bit--) {
			if(parent[a][bit] != parent[b][bit]) {
				a = parent[a][bit];
				b = parent[b][bit];
			}
		}
		return parent[a][0];
	};
	

	vector<int> counts(n);
	for(int i = 0; i < m; i++) {
		int s;
		cin >> s;
		vector<pair<int, int>> minister;
		for(int j = 0; j < s; j++) {
			int track;
			cin >> track;
			track--;
			minister.push_back({order[track], track});
		}
		sort(minister.begin(), minister.end());
		for(int j = 0; j < s; j++) {
			int a = minister[j].second;
			int b = minister[(j+1)%s].second;
			counts[a]++;
			counts[b]++;
			int LCA = lca(a, b);
			counts[LCA]-=2;
		}
	}
	
	vector<int> necessary(n);
	function<int(int)> search = [&](int curr) {
		int count = counts[curr];
		for(int next : con[curr]) {
			if(next != parent[curr][0])
				count += search(next);
		}
		necessary[curr] = count;
		return count;
	};
	search(0);
	
	vector<int> ans;
	for(int i = 0; i < n-1; i++) {
		int a = edges[i].first;
		int b = edges[i].second;
		if(depth[a] < depth[b])
			swap(a, b);
		necessary[a] /= 2;
		if(necessary[a] >= k)
			ans.push_back(i+1);
	}

	
	cout << ans.size() << "\n";
	for(int a : ans)
		cout << a << " ";
	cout << "\n";
	
}