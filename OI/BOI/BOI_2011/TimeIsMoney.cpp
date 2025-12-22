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

constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> edge(m);
	vector<ll> t(m);
	vector<ll> c(m);
	for(int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y >> t[i] >> c[i];
		edge[i] = {x, y};
	}
	
	pair<ll, ll> best{INF, INF};
	vector<pair<int, int>> ans;
	vector<int> order(m);
	iota(all(order), 0);
	
	auto check = [&]() {
		vector<int> p(n);
		vector<int> size(n, 1);
		iota(all(p), 0);
		function<int(int)> getPar = [&](int a) {
			if(a == p[a])
				return a;
			return p[a] = getPar(p[a]);
		};
		int merges = 0;
		auto merge = [&](int a, int b) {
			a = getPar(a);
			b = getPar(b);
			if(a == b)
				return false;
			if(size[a] < size[b])
				swap(a, b);
			size[a] += size[b];
			p[b] = a;
			return true;
		};
		vector<pair<int, int>> take;
		pair<ll, ll> cost{0,0};
		for(auto i : order) {
			auto [a,b] = edge[i];
			if(merge(a,b)) {
				take.push_back({a, b});
				cost.first += t[i];
				cost.second += c[i];
				merges++;
			}
			if(merges == n-1)
				break;
		}
		if(cost.first*cost.second < best.first*best.second) {
			best = cost;
			ans = take;
		}
		return cost;
	};
	
	auto sortLeft = [&](ll T, ll C) {
		sort(all(order), [&](int a, int b) {
			ll aVal = T*t[a]+C*c[a];
			ll bVal = T*t[b]+C*c[b];
			return aVal==bVal ? t[a]<t[b] : aVal < bVal;
		});
	};
	auto sortRight = [&](ll T, ll C) {
		sort(all(order), [&](int a, int b) {
			ll aVal = T*t[a]+C*c[a];
			ll bVal = T*t[b]+C*c[b];
			return aVal==bVal ? c[a]<c[b] : aVal < bVal;
		});
	};
	
	sortRight(1,0);
	auto l = check();
	sortLeft(0,1);
	auto r = check();

	queue<pair<pair<ll, ll>, pair<ll, ll>>> q;
	q.push({l, r});
	while(!q.empty()) {
		auto [left, right] = q.front();
		q.pop();
		pair<ll, ll> mid = {left.second-right.second, right.first-left.first};
		sortLeft(mid.first, mid.second);
		auto res = check();
		if(res == left || res == right)
			continue;
		q.push({left, res});
		sortRight(mid.first, mid.second);
		res = check(); 
		if(res == left || res == right)
			continue;
		q.push({res, right});
	}
	
	cout << best.first << " " << best.second << "\n";
	for(auto [a,b] : ans)
		cout << a << " " << b << "\n";
}