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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		vector<int> deg(n);
		for(int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
			deg[u]++;
			deg[v]++;
		}
		vector<int> fromLeaf(n, n+5);
		vector<bool> vis(n);
		queue<int> q;
		ll leaves = 0;
		for(int i = 0; i < n; i++) {
			if(deg[i] == 1) {
				fromLeaf[i] = 0;
				q.push(i);
				leaves++;
			}
		}
		ll nonLeaves = n-leaves;
		ll twoOut = 0;
		while(!q.empty()) {
			auto curr = q.front();
			q.pop();
			if(vis[curr])
				continue;
			vis[curr] = true;
			if(fromLeaf[curr] >= 2)
				twoOut++;
			for(int next : con[curr]) {
				fromLeaf[next] = min(fromLeaf[next], fromLeaf[curr]+1);
				if(vis[next])
					continue;
				deg[next]--;
				if(deg[next] <= 1)
					q.push(next);
			}
		}
		vector<int> subtree(n);
		ll other = 0;
		function<void(int, int)> dfs = [&](int curr, int prev) {
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
				subtree[curr] += subtree[next];
			}
			if(fromLeaf[curr] >= 2)
				subtree[curr]++;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				if(fromLeaf[curr] >= 1 && fromLeaf[next] == 1)
					other += subtree[next];
				if(fromLeaf[curr] == 1 && fromLeaf[next] >= 1)
					other += twoOut-subtree[next];
			}
		};
		dfs(0, -1);
		// cout << leaves << " " << nonLeaves << "\n";
		// cout << leaves*nonLeaves << " " << other << endl;
		cout << leaves*nonLeaves + other << "\n";
	}
}