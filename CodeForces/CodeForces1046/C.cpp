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

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		ll V;
		cin >> n >> m >> V;
		vector<int> weight(n);
		for(int i = 0; i < n; i++)
			cin >> weight[i];
		vector<vector<int>> adj(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		
		// https://cp-algorithms.com/graph/bridge-searching.html
		set<pair<int, int>> bridges;
		auto ADD_BRIDGE = [&](int v, int to) {
			bridges.insert({min(v, to), max(v, to)});
		};
		
		auto find_bridges = [&](){
			vector<bool> visited(n, false);
			vector<int> tin(n, -1), low(n, -1);
			int timer = 0;
		    function<void(int, int)> dfs = [&](int v, int p) {
			    visited[v] = true;
			    tin[v] = low[v] = timer++;
			    bool parent_skipped = false;
			    for (int to : adj[v]) {
			        if (to == p && !parent_skipped) {
			            parent_skipped = true;
			            continue;
			        }
			        if (visited[to]) {
			            low[v] = min(low[v], tin[to]);
			        } else {
			            dfs(to, v);
			            low[v] = min(low[v], low[to]);
			            if (low[to] > tin[v])
			                ADD_BRIDGE(v, to);
			        }
			    }
			};
		    for(int i = 0; i < n; ++i) {
		        if (!visited[i])
		            dfs(i, -1);
		    }
		};
		find_bridges();
		
		auto is_bridge = [&](int a, int b) {
			return bridges.count({min(a, b), max(a, b)}) > 0;
		};
		
		ll ans = 1;
		vector<int> color(n, -1);
		int cnt = 0;
		bool odd = false;
		set<int> W;
		
		function<void(int, int)> go = [&](int curr, int C) {
			color[curr] = C;
			cnt++;
			if(weight[curr] != -1)
				W.insert(weight[curr]);
			for(int next : adj[curr]) {
				if(is_bridge(curr, next))
					continue;
				if(color[next] != -1) {
					if(color[next] == C)
						odd = true;
					continue;
				}
				go(next, C^1);
			}
		};
		

		for(int i = 0; i < n; i++) {
			if(color[i] == -1) {
				W.clear();
				cnt = 0;
				odd = false;
				go(i, 0);
				// single guy
				if(cnt == 1) {
					if(W.empty())
						ans = ans*V%MOD;
					continue;
				}
				// otherwise in a cycle
				if(sz(W) > 1)
					ans = 0;
				// odd cycle must be 0
				if(odd) {
					if(!W.empty() && *W.begin() != 0)
						ans = 0;
				}
				else {
					if(W.empty())
						ans = ans*V%MOD;
				}
			}
		}
		cout << ans << "\n";
		
	}
}