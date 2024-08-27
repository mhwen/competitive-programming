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

constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<bool> edgeUsed(m);
	vector<pair<int, int>> edges(m);
	vector<ll> w(m);
	vector<vector<pair<int, int>>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b >> w[i];
		a--; b--;
		edges[i] = {a, b};
		con[a].push_back({b, i});
		con[b].push_back({a, i});
	}
	priority_queue<pair<ll, pair<int, int>>> q;
	vector<bool> vis(n);
	q.push({0, {0, -1}});
	ll mst = 0;
	while(!q.empty()) {
		auto p = q.top();
		q.pop();
		ll dist = -p.first;
		int curr = p.second.first;
		int fromEdge = p.second.second;
		if(vis[curr])
			continue;
		if(fromEdge != -1)
			edgeUsed[fromEdge] = true;
		vis[curr] = true;
		mst += dist;
		for(auto [next,edge]: con[curr]) {
			if(vis[next])
				continue;
			q.push({-w[edge], {next, edge}});
		}
	}
	vector<int> order(n);
	vector<int> dep(n);
	vector<int> sizes(n, 1);
	vector<vector<int>> par(30, vector<int>(n));
	int id = 0;
	function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
		order[curr] = id++;
		par[0][curr] = prev;
		dep[curr] = d;
		for(auto [next,edge]: con[curr]) {
			if(!edgeUsed[edge])
				continue;
			if(next == prev)
				continue;
			dfs(next, curr, d+1);
			sizes[curr] += sizes[next];
		}
	};
	dfs(0, 0, 0);
	for(int bit = 1; bit < 30; bit++) {
		for(int i = 0; i < n; i++)
			par[bit][i] = par[bit-1][par[bit-1][i]];
	}

	auto lca = [&](int a, int b) {
		for(int bit = 29; bit >= 0; bit--) {
			if(dep[a]-dep[b] >= (1<<bit))
				a = par[bit][a];
			if(dep[b]-dep[a] >= (1<<bit))
				b = par[bit][b];
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

	vector<ll> tree(2*n, INF);
	auto update = [&](int p, ll val) {
		p += n;
		tree[p] = val;
		p /= 2;
		while(p > 0) {
			tree[p] = min(tree[p*2], tree[p*2+1]);
			p /= 2;
		}
	};
	
	auto query = [&](int l, int r) {
		ll res = INF;
		l += n; r += n;
		for(; l <= r; l/=2, r/=2) {
			if(l%2==1) {
				res = min(tree[l], res);
				l++;
			}
			if(r%2==0) {
				res = min(tree[r], res);
				r--;
			}
		}
		return res;
	};

	vector<vector<pair<int, ll>>> toAdd(n);
	vector<ll> bestEdge(n, INF);
	for(int i = 0; i < m; i++) {
		if(!edgeUsed[i]) {
			int a = edges[i].first;
			int b = edges[i].second;
			ll weight = w[i];
			int Lca = lca(a, b);
			toAdd[Lca].push_back({a, weight});
			toAdd[Lca].push_back({b, weight});
		}
	}
	
	ll best = mst;
	
	function<void(int, int)> solve = [&](int curr, int parEdge) {
		if(parEdge != -1) {
			best = max(best, mst-w[parEdge]+query(order[curr], order[curr]+sizes[curr]-1));
		}
		for(auto [node, weight]: toAdd[curr]) {
			bestEdge[node] = min(bestEdge[node], weight);
			update(order[node], bestEdge[node]);
		}
		for(auto [next,edge]: con[curr]) {
			if(!edgeUsed[edge])
				continue;
			if(edge == parEdge)
				continue;
			solve(next, edge);
		}
	};
	solve(0, -1);
	cout << best << "\n";
}