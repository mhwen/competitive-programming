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
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<bool>> reachable(n, vector<bool>(n));
	vector<vector<int>> con(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		con[u].push_back(v);
	}
	
	vector<bool> reached(n);
	int from = -1;
	int target = -1;
	
	function<bool(int)> dfs = [&](int curr) {
		if(reached[curr])
			return false;
		reached[curr] = true;
		reachable[from][curr] = true;
		if(curr == target)
			return true;
		
		for(int next : con[curr]) {
			if(!reached[next])
				if(dfs(next))
					return true;
		}
		return false;
	};
	
	while(q-->0) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		if(reachable[y][x]) {
			cout << "YES\n";
		}
		else {
			reached = vector<bool>(n);
			from = y;
			target = x;
			dfs(y);
			if(reachable[y][x]) {
				cout << "YES\n";
			}
			else
				cout << "NO\n";
		}
		con[x].push_back(y);
	}
}