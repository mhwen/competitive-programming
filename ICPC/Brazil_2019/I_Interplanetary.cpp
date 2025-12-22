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

constexpr ll INF = 1e17;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, r;
	cin >> n >> r;
	vector<ll> temps(n);
	for(int i = 0; i < n; i++) {
		cin >> temps[i];
	}
	vector<ll> u = temps;
	sort(all(u));
	u.erase(unique(all(u)), u.end());
	
	auto comp = [&](ll t) {
		return (int)(lower_bound(all(u), t)-u.begin());
	};
	
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		int aT = comp(temps[a]);
		int bT = comp(temps[b]);
		return aT < bT;
	});
	
	vector<pair<ll, pair<int, int>>> edges(r);
	vector<vector<int>> con(n);
	for(int i = 0; i < r; i++) {
		int x, y;
		ll d;
		cin >> x >> y >> d;
		x--; y--;
		edges[i] = {d, {x, y}};
		con[x].push_back(i);
		con[y].push_back(i);
	}
	
	int q;
	cin >> q;
	vector<pair<pair<int, int>, pair<int, int>>> loQ;
	vector<pair<pair<int, int>, pair<int, int>>> hiQ;
	for(int i = 0; i < q; i++) {
		int a, b, k, t;
		cin >> a >> b >> k >> t;
		a--; b--;
		if(t == 0)
			loQ.push_back({{min(sz(u)-1, k-1), i}, {a, b}});
		else
			hiQ.push_back({{max(0, sz(u)-k), i}, {a, b}});
	}
	sort(all(loQ));
	sort(all(hiQ));
	reverse(all(hiQ));
	
	vector<ll> ans(q, INF);
	vector<vector<ll>> dist(n, vector<ll>(n));
	
	auto initDists = [&]() {
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dist[i][j] = INF;
		for(int i = 0; i < n; i++)
			dist[i][i] = 0;
		for(auto [d, e] : edges) {
			int from = e.first;
			int to = e.second;
			dist[from][to] = d;
			dist[to][from] = d;
		}
	};
	initDists();

	//lo temps
	int qId = 0;
	for(auto add : order) {
		int myTemp = comp(temps[add]);
		while(qId < sz(loQ) && myTemp > loQ[qId].first.first) {
			auto query = loQ[qId];
			int from = query.second.first;
			int to = query.second.second;
			ans[query.first.second] = dist[from][to];
			qId++;
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][add]+dist[add][j]);
			}
		}
	}
	while(qId < sz(loQ)) {
		auto query = loQ[qId];
		int from = query.second.first;
		int to = query.second.second;
		ans[query.first.second] = dist[from][to];
		qId++;
	}
	
	//hi temps
	initDists();
	reverse(all(order));
	qId = 0;
	for(auto add : order) {
		int myTemp = comp(temps[add]);
		while(qId < sz(hiQ) && myTemp < hiQ[qId].first.first) {
			auto query = hiQ[qId];
			int from = query.second.first;
			int to = query.second.second;
			ans[query.first.second] = dist[from][to];
			qId++;
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][add]+dist[add][j]);
			}
		}
	}
	while(qId < sz(hiQ)) {
		auto query = hiQ[qId];
		int from = query.second.first;
		int to = query.second.second;
		ans[query.first.second] = dist[from][to];
		qId++;
	}
	
	for(ll l : ans) {
		if(l == INF)
			cout << -1 << "\n";
		else
			cout << l << "\n";
	}
	
}