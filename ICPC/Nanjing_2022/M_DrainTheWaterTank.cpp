#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
using pii = pair<int, int>;
auto cross(pii a, pii b, pii c) {
	
}

vector<pair<int, int>> delete_collinear(const vector<pair<int, int>> &pts) {
	vector<pair<int, int>> res;
	for (auto p : pts) {
		if (res.empty() || res.back())
	}
}
*/

#define x first
#define y second

/*
bool inside(vector<pair<int, int>> &pts, pair<int, int> p) {
	int n = (int) pts.size();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto c = pts[i];
		auto nn = pts[(i + 1) % n];
	
		if (c.first < nn.first) swap(c, nn);	
		if (c.first == nn.first) continue;
		
		if (c.first < p.first && p.first < nn.first) {
			// frac is (p.x - c.x) / (nn.x - c.x)
			auto num = (ll)(nn.second - c.second) * (p.first - c.first);
			auto denom = (ll) nn.x - c.x;
			num += denom * c.first;
			
			if (num >= denom * p.second) ans++;
		}
	}
	
	return ans % 2 == 1;
}
*/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<pair<int, int>> pts(n);
	for (auto &[x, y] : pts) {
		cin >> x >> y;
	}
	
	
	vector<bool> inside(n);
	for (int i = 0; i < n; i++) {
		auto p = pts[(i + n - 1) % n];
		auto c = pts[i];
		auto nn = pts[(i + 1) % n];
		
		pair<int, int> v1 = {c.first - p.first, c.second - p.second};
		pair<int, int> v2 = {nn.first - c.first, nn.second - c.second};
		
		auto cross = (ll) v1.first * v2.second - (ll) v1.second * v2.first;
			
		if (cross >= 0) {
			inside[i] = true;
		}
	}
	
	/*
	vector<pair<int, int>> pts2;
	for (int i = 0; i < n; i++) {
		auto p = pts[i];
		if (pts2.empty() || pts2.back().second != p.second) {
			pts2.push_back({i, p.second});
		}
	}
	
	while (pts2.back().second == pts2[0].second) {
		pts2.pop_back();
	}
	
	n = (int) pts2.size();
	pts = pts2;
	
	
	// for (auto p : pts) cout << p.first << ' ' << p.second << '\n';
	
	vector<bool> true_min(n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto p = pts[(i + n - 1) % n];
		auto c = pts[i];
		auto nn = pts[(i + 1) % n];
			
		if (inside[c.first]) {
			true_min[i] = c.second < min(p.second, nn.second);
			if (true_min[i]) ans++;
		}
	}
	
	cout << ans << '\n';
	*/
	
	vector<int> pts_sorted(n);
	iota(pts_sorted.begin(), pts_sorted.end(), 0);
	queue<int> q;
	sort(pts_sorted.begin(), pts_sorted.end(), [&](int i, int j) {
		auto p1 = pts[i];
		auto p2 = pts[j];
		if (p1.second == p2.second) return p1.first < p2.first;
		return p1.second < p2.second;
	});
		
	vector<bool> flows_to_min(n);
	
	int ans = 0;
	for (auto src : pts_sorted) {
		if (flows_to_min[src]) continue;
		if (inside[src]) ans++;
		q.push(src);
		while (!q.empty()) {
			auto v = q.front();
			q.pop();
					
			if (flows_to_min[v]) continue;
			flows_to_min[v] = true;
			
			auto p = pts[(v + n - 1) % n];
			auto c = pts[v];
			auto nn = pts[(v + 1) % n];
			
			if (c.second <= p.second) {
				q.push((v + n - 1) % n);
			}
			
			if (c.second <= nn.second) {
				q.push((v + 1) % n);
			}
		}
	}
	
	cout << ans << '\n';
	
	/*
	int ans = 0;
	for (int i = 0; i < n; i++) {
		auto p = pts[(i + n - 1) % n];
		auto c = pts[i];
		auto nn = pts[(i + 1) % n];
		
		if (flows_to_min[i]) {
			if (true_min[i]) {
				ans++;
			}
		} else {
			// needs to be horizontal, first one
			if (p.second == c.second && c.second < nn.second) {
				ans++;
			}
		}
	}
	
	cout << ans << '\n';
	*/
	
	return 0;
}