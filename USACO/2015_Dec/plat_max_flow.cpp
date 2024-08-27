#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("maxflow.in");
	ofstream cout("maxflow.out");
	int n, k;
	cin >> n >> k;
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	vector<int> depth(n);
	vector<vector<int>> parent(30, vector<int>(n));
	function<void(int, int, int)> dfs = [&](int curr, int prev, int dep) {
		depth[curr] = dep;
		for(int next : con[curr]) {
			if(next != prev) {
				parent[0][next] = curr;
				dfs(next, curr, dep+1);
			}
		}
	};
	dfs(0, 0, 0);
	
	for(int bit = 1; bit < 30; bit++) {
		for(int i = 0; i < n; i++) {
			parent[bit][i] = parent[bit-1][parent[bit-1][i]];
		}
	}
	
	auto lca = [&] (int a, int b) {
		if(depth[a] < depth[b])
			swap(a, b);
		int diff = depth[a]-depth[b];
		for(int bit = 0; bit < 30; bit++) {
			if(diff%2)
				a = parent[bit][a];
			diff /= 2;
		}
		if(a == b)
			return a;
		for(int bit = 29; bit >= 0; bit--) {
			if(parent[bit][a] != parent[bit][b]) {
				a = parent[bit][a];
				b = parent[bit][b];
			}
		}
		return parent[0][a];
	};
	
	vector<int> flow(n);
	
	for(int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		int LCA = lca(a, b);
		flow[a]++;
		flow[b]++;
		flow[LCA]--;
		if(LCA != 0)
			flow[parent[0][LCA]]--;
	}
	
	int ans = 0;
	
	function<int(int, int)> findFlow = [&](int curr, int prev) {
		int amt = flow[curr];
		for(int next : con[curr]) {
			if(next != prev) {
				amt += findFlow(next, curr);
			}
		}
		ans = max(ans, amt);
		return amt;
	};
	
	findFlow(0, 0);
	
	cout << ans << "\n";
}