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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, m;
	cin >> n >> k >> m;
	vector<int> deg(n);
	vector<vector<int>> con(n);
	for(int i = 0; i < k; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		con[u].push_back(v);
		deg[v]++;
	}
	vector<vector<int>> aboveNode(n);
	for(int i = 0; i < m; i++) {
		int s, t;
		cin >> s >> t;
		s--; t--;
		aboveNode[t].push_back(s);
	}
	int ans = 0;
	vector<int> dep(n);
	function<int(int, int)> dfs = [&](int curr, int d) {
		dep[curr] = d;
		int need = -1;
		for(int node : aboveNode[curr])
			need = max(need, dep[node]);
		for(int next : con[curr])
			need = max(need, dfs(next, d+1));
		if(need == d) {
			ans++;
			need = -1;
		}
		return need;
	};
	for(int i = 0; i < n; i++) {
		if(deg[i] == 0)
			dfs(i, 0);
	}
	cout << ans << "\n";
}