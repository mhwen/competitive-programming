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

vector<ll> calculate_costs(vector<int> w, vector<int> A, vector<int> B, vector<int> e) {
	int n = sz(w);
	int q = sz(e);
	ll total = accumulate(all(A), 0LL);
	
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		return w[a] < w[b];
	});
	
	auto reorder = [&](vector<int>& v) {
		vector<int> hold(n);
		for(int i = 0; i < n; i++) {
			hold[i] = v[order[i]];
		}
		v = hold;
	};
	reorder(w);
	reorder(A);
	reorder(B);
	
	vector<int> par(n);
	vector<pair<int, int>> bounds(n);
	for(int i = 0; i < n; i++)
		bounds[i] = {i, i};
	vector<vector<ll>> best(n, vector<ll>(2, INF));
	vector<vector<ll>> bestExtra(n, vector<ll>(2, INF));
	vector<int> sizes(n, 1);
	vector<ll> sums(n);
	for(int i = 0; i < n; i++) {
		sums[i] = A[i]-B[i];
		best[i][i%2] = A[i]-B[i];
	}
	iota(all(par), 0);
	
	ll curr = 0;
	
	auto getCost = [&](int a) {
		int parity = bounds[a].first%2;
		int len = bounds[a].second-bounds[a].first+1;
		ll res = sums[a];
		if(len%2==1)
			res -= min(best[a][parity], bestExtra[a][parity^1]);
		return res;
	};
	
	function<int(int)> getPar = [&](int a) {
		if(a == par[a])
			return a;
		return par[a] = getPar(par[a]);
	};
	auto merge = [&](int a, int b) {
		a = getPar(a);
		b = getPar(b);
		if(a == b)
			return;
		if(sizes[a] < sizes[b])
			swap(a, b);
		curr -= getCost(a);
		curr -= getCost(b);
		
		par[b] = a;
		sizes[a] += sizes[b];
		sums[a] += sums[b];
		for(int i = 0; i <= 1; i++) {
			best[a][i] = min(best[a][i], best[b][i]);
			bestExtra[a][i] = min(bestExtra[a][i], bestExtra[b][i]);
		}
		bounds[a].first = min(bounds[a].first, bounds[b].first);
		bounds[a].second = max(bounds[a].second, bounds[b].second);
		curr += getCost(a);
	};
	
	vector<pair<int, pair<int, int>>> events;
	for(int i = 0; i < q; i++) {
		events.emplace_back(e[i], pair{2, i});
	}
	for(int i = 1; i < n; i++) {
		events.emplace_back(w[i]-w[i-1], pair{0, i});
		if(i > 1)
			events.emplace_back(w[i]-w[i-2], pair{1, i-1});
	}
	sort(all(events));
	
	vector<ll> ans(q);
	for(auto [_, id] : events) {
		if(id.first == 0) {
			merge(id.second-1, id.second);
		}
		else if(id.first == 1) {
			int guy = id.second;
			int parent = getPar(guy);
			curr -= getCost(parent);
			bestExtra[parent][guy%2] = min(bestExtra[parent][guy%2], (ll)A[guy]-B[guy]);
			curr += getCost(parent);
		}
		else {
			ans[id.second] = total-curr;
		}
	}
	return ans;
}

// int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);
	// int n;
	// cin >> n;
	// vector<int> w(n);
	// vector<int> A(n);
	// vector<int> B(n);
	// for(int i = 0; i < n; i++)
		// cin >> w[i] >> A[i] >> B[i];
	// int q;
	// cin >> q;
	// vector<int> e(q);
	// for(int i = 0; i < q; i++)
		// cin >> e[i];
	// auto res = calculate_costs(w, A, B, e);
	// for(ll l : res)
		// cout << l << "\n";
// }