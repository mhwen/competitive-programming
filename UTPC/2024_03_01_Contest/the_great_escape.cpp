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
	int n, m, k;
	cin >> n >> m >> k;
	vector<ll> x(k);
	vector<ll> y(k);
	vector<ll> r(k);
	for(int i = 0; i < k; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}
	vector<vector<int>> con(k);
	for(int i = 0; i < k; i++) {
		for(int j = i+1; j < k; j++) {
			ll dx = x[i]-x[j];
			ll dy = y[i]-y[j];
			if(dx*dx+dy*dy <= (r[i]+r[j])*(r[i]+r[j])) {
				con[i].push_back(j);
				con[j].push_back(i);
			}
		}
	}
	queue<pair<int, int>> q;
	vector<bool> vis(k);
	for(int i = 0; i < k; i++) {
		if(x[i]-r[i] <= 0 || y[i]+r[i] >= m)
			q.push({1, i});
	}
	int ans = -1;
	while(!q.empty()) {
		auto cc = q.front();
		q.pop();
		int curr = cc.second;
		int dist = cc.first;
		if(vis[curr])
			continue;
		vis[curr] = true;
		if(x[curr]+r[curr] >= n || y[curr]-r[curr] <= 0) {
			ans = dist;
			break;
		}
		for(int next : con[curr]) {
			if(!vis[next])
				q.push({dist+1, next});
		}
	}
	cout << ans << "\n";
}