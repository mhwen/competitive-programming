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
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> con(n);
		vector<int> degree(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
			degree[a]++;
			degree[b]++;
		}
		vector<vector<int>> par(30, vector<int>(n));
		vector<int> lift(n);
		vector<int> depth(n);
		function<void(int, int, int)> dfs = [&](int curr, int prev, int dep) {
			par[0][curr] = prev;
			lift[curr] = curr;
			if(curr != n-1) {
				if(prev == n-1) {
					if(degree[prev] == 1)
						lift[curr] = lift[prev];
				}
				else {
					if(degree[prev] == 2)
						lift[curr] = lift[prev];
				}
			}
			depth[curr] = dep;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, dep+1);
			}
		};
		
		dfs(n-1, n-1, 0);
		
		for(int bit = 1; bit < 30; bit++) {
			for(int i = 0; i < n; i++) {
				par[bit][i] = par[bit-1][par[bit-1][i]];
			}
		}
		
		function<int(int, int)> lca = [&](int a, int b) {
			if(depth[a] < depth[b])
				swap(a, b);
			for(int bit = 29; bit >= 0; bit--) {
				if(depth[a]-depth[b] >= (1<<bit))
					a = par[bit][a];
			}
			if(a == b)
				return a;
			for(int bit = 29; bit >= 0; bit--) {
				if(par[bit][a] != par[bit][b]) {
					a = par[bit][a];
					b = par[bit][b];
				}
			}
			return par[0][a];
		};
		
		bool escape = false;
		function<int(int, int)> check = [&](int curr, int prev) {
			//at a leaf
			if(curr < m) {
				int them = lift[(curr+1)%m];
				if(depth[them] < depth[lift[curr]])
					escape = true;
				return them;
			}
			int LCA = -1;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				int them = check(next, curr);
				if(LCA == -1)
					LCA = them;
				else
					LCA = lca(LCA, them);
				LCA = lift[LCA];
			}
			LCA = lift[LCA];
			if(depth[LCA] < depth[lift[curr]])
				escape = true;
			return LCA;
		};
		
		check(n-1, n-1);
		
		if(escape)
			cout << "Tie\n";
		else
			cout << "Doddle\n";
	}
}