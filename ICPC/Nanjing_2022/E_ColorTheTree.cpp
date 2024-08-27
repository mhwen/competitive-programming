#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cassert>

using namespace std;

typedef long long ll;

constexpr ll INF = 1e16;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for(int pw = 1, k = 1; pw * 2 <=sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b);
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> costs(n);
		for(int i = 0; i < n; i++) {
			cin >> costs[i];
		}
		RMQ<ll> rmq(costs);
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
		}
		vector<vector<int>> depths(n+1);
		vector<int> myDepth(n);
		vector<vector<int>> anc(n, vector<int>(30));
		
		function<void(int, int, int)> dfs = [&](int curr, int prev, int depth) {
			depths[depth].push_back(curr);
			myDepth[curr] = depth;
			anc[curr][0] = prev;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, depth+1);
			}
		};
		
		dfs(0, 0, 0);
		
		
		for(int bit = 1; bit < 30; bit++) {
			for(int i = 0; i < n; i++) {
				anc[i][bit] = anc[anc[i][bit-1]][bit-1];
			}
		}
		
		function<int(int, int)> LCA = [&](int a, int b) {
			if(myDepth[a] < myDepth[b])
				swap(a, b);
			while(myDepth[a] > myDepth[b])
				a = anc[a][0];
			if(a == b)
				return a;
			for(int bit = 29; bit >= 0; bit--) {
				if(anc[a][bit] != anc[b][bit]) {
					a = anc[a][bit];
					b = anc[b][bit];
				}
			}
			return anc[a][0];
		};
		
		
		function<ll(int, int, int, int)> solveDFS = [&](int curr, int prev, int depth, int target) {
			if(depth == target)
				return costs[0];
				
			ll childCosts = 0;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				childCosts += solveDFS(next, curr, depth+1, target);
			}
			// cout << "ans at " << curr << " is " << min(childCosts, costs[target-depth]) << endl;
			return min(childCosts, costs[target-depth]);
		};
		
		function<ll(vector<int>&, int)> solveDP = [&](vector<int>& nodes, int depth) {
			vector<ll> dp(nodes.size()+1, INF);
			dp[0] = 0;
			for(int i = 1; i < (int)dp.size(); i++) {
				for(int j = 0; j < i; j++) {
					int lca = LCA(nodes[j], nodes[i-1]);
					// cout << "lca of " << nodes[i-1] << " " << nodes[j] << " is " << lca << endl;
					int distNeeded = depth-myDepth[lca];
					ll cost = rmq.query(distNeeded, depth+1);
					dp[i] = min(dp[i], dp[j]+cost);
				}
				// cout << "node " << nodes[i-1] << " costs " << dp[i] << endl;
			}
			return dp.back();
		};
		
		
		int rootN = 500;
		
		ll ans = 0;
		
		for(int depth = 0; depth <= n; depth++) {
			if((int)depths[depth].size() >= rootN) {
				// cout << "dfsing at depth " << depth << endl; 
				ans += solveDFS(0, -1, 0, depth);
			}
			else {
				// cout << "dping at depth " << depth << endl;
				ans += solveDP(depths[depth], depth);
			}
		}
		cout << ans << "\n";
	}
}