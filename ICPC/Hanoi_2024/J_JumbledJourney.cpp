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

struct FT {
	vector<int> s;
	FT(int n) : s(n) {}
	void update(int pos, int dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	int query(int pos) { // sum of values in [0, pos)
		int res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
};

void solve(int n, vector<pair<int, int>>& edges, vector<int>& w) {
	vector<int> in(n);
	int id = 0;
	vector<vector<int>> con(n);
	for(auto [a, b] : edges) {
		con[a].push_back(b);
		con[b].push_back(a);
	}
	vector<int> size(n, 1);
	vector<int> par(n, -1);
	function<void(int, int)> dfs = [&](int curr, int prev) {
		in[curr] = id++;
		par[curr] = prev;
		for(int next : con[curr]) {
			if(next == prev)
				continue;
			dfs(next, curr);
			size[curr] += size[next];
		}
	};
	dfs(0, -1);
	vector<int> edgeOrder(sz(edges));
	iota(all(edgeOrder), 0);
	sort(all(edgeOrder), [&](int a, int b) {
		return w[a] > w[b];
	});
	FT tree(n);
	for(int i = 0; i < n; i++)
		tree.update(i, 1);
	vector<bool> used(n);
	auto getComp = [&](int start, int prev) {
		vector<int> comp;
		queue<int> q;
		q.push(start);
		while(!q.empty()) {
			auto curr = q.front();
			q.pop();
			if(used[curr])
				continue;
			comp.push_back(curr);
			used[curr] = true;
			for(auto next : con[curr]) {
				if(next == prev || used[next])
					continue;
				q.push(next);
			}
		}
		return comp;
	};
	ll ans = 0;
	int rem = n;
	vector<int> perm;
	vector<int> giveBack;
	auto solve = [&](int eId, int give, auto&& self) -> void {
		auto [a, b] = edges[edgeOrder[eId]];
		ll edgeWeight = w[edgeOrder[eId]];
		if(par[b] == a)
			swap(a, b);
		int below = tree.query(in[a]+size[a])-tree.query(in[a]);
		int above = rem-below;
		if(below > above) {
			swap(below, above);
			swap(a, b);
		}
		vector<int> small = getComp(a, b);
		vector<int> big;
		for(int node : small)
			tree.update(in[node], -1);
		rem -= sz(small);
		if(above-give <= below+1) {		
			big = getComp(b, a);
			for(int i = 0; i < give; i++) {
				if(sz(big) > sz(small)) {
					giveBack.push_back(big.back());
					big.pop_back();
				}
				else {
					giveBack.push_back(small.back());
					small.pop_back();
				}
			}
			ans += edgeWeight*(sz(big)+sz(small)-1);
		}
		else {
			self(eId+1, sz(small)+give, self);
			for(int i = 0; i < sz(small); i++) {
				big.push_back(giveBack.back());
				giveBack.pop_back();
			}
			ans += edgeWeight*(sz(big)+sz(small));
		}
		if(sz(big) > sz(small))
			perm.push_back(big.back());
		for(int i = 0; i < sz(small); i++) {
			perm.push_back(small[i]);
			perm.push_back(big[i]);
		}
	};
	solve(0, 0, solve);
	cout << ans << "\n";
	for(auto p : perm)
		cout << p+1 << " ";
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<pair<int, int>> edges(m);
		vector<int> w(m);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b >> w[i];
			a--; b--;
			edges[i] = {a, b};
		}
		vector<bool> used(m);
		vector<int> p(n);
		vector<int> size(n, 1);
		iota(all(p), 0);
		function<int(int)> par = [&](int a) {
			if(a == p[a])
				return a;
			return p[a] = par(p[a]);
		};
		auto merge = [&](int a, int b) {
			a = par(a);
			b = par(b);
			if(a == b)
				return false;
			if(size[a] > size[b])
				swap(a, b);
			p[a] = b;
			size[b] += size[a];
			return true;
		};
		vector<int> edgeOrder(m);
		iota(all(edgeOrder), 0);
		sort(all(edgeOrder), [&](int a, int b) {
			return w[a] < w[b];
		});
		vector<pair<int, int>> usedEdges;
		vector<int> usedWeights;
		for(auto e : edgeOrder) {
			if(merge(edges[e].first, edges[e].second)) {
				usedEdges.push_back(edges[e]);
				usedWeights.push_back(w[e]);
			}
		}
		solve(n, usedEdges, usedWeights);
	}
}