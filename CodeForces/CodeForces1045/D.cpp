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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].pb(v);
			con[v].pb(u);
		}
		vector<int> dist(n);
		vector<int> p(n);
		int x;
		function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
			dist[curr] = d;
			p[curr] = prev;
			if(dist[curr] > dist[x])
				x = curr;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, d+1);
			}
		};
		auto go = [&](int s) {
			x = s;
			dfs(s, -1, 0);
			return x;
		};
		int y = go(0);
		int z = go(y);
		vector<int> ans{-1};
		
		while(z != y) {
			int w = p[z];
			if(sz(con[w]) > 2) {
				for(int next : con[w]) {
					if(next != z && next != p[w]) {
						ans = {z+1, w+1, next+1};
						break;
					}
				}
			}
			z = w;
		}
		for(int a : ans)
			cout << a << " ";
		cout << "\n";
	}
}