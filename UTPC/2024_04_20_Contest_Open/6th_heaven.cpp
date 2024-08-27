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
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<vector<int>> con(n);
	vector<int> degree(n);
	for(int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}

	vector<bool> vis(n);
	
	function<bool(int, int)> dfs = [&](int curr, int prev) -> bool {
		if(vis[curr])
			return true;
		vis[curr] = true;
		for(int next : con[curr]) {
			if(next == prev)
				continue;
			if(dfs(next, curr))
				return true;
		}
		return false;
	};
	
	ll ways = 1;
	ll segments = 0;
	
	for(int i = 0; i < n; i++) {
		if(degree[i] > 2) {
			ways = -1;
			break;
		}
		if(vis[i])
			continue;
		segments++;
		if(degree[i] == 0)
			continue;
		ways *= 2;
		ways %= MOD;
		if(dfs(i, -1)) {
			ways = -1;
			break;
		}
	}
	if(ways != -1) {
		for(int i = 1; i <= segments; i++) {
			ways *= i;
			ways %= MOD;
		}
	}

	cout << ways << "\n";
}