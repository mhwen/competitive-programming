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
	vector<vector<bool>> adj(n+1, vector<bool>(n+1));
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
	for(int i = 0; i < n; i++)
		adj[n][i] = true;
	
	int best = 0;
	vector<bool> vis(n);
	function<void(int, int, int)> permute = [&](int id, int curr, int x) {
		// cout << id << " " << curr << " " << x << endl;
		best = max(best, x);
		if(id == n) {
			return;
		}
		for(int next = 0; next < n; next++) {
			if(vis[next])
				continue;
			if(!adj[curr][next])
				continue;
			vis[next] = true;
			permute(id+1, next, x^vals[next]);
			vis[next] = false;
		}
	};
	
	permute(0, n, 0);
	cout << best << "\n";
}