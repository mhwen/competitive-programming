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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll m, n;
	int k;
	cin >> m >> n >> k;
	vector<ll> x(k);
	vector<ll> y(k);
	vector<ll> r(k);
	for(int i = 0; i < k; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}
	
	auto touch = [&](int i, int j) {
		ll dx = x[i]-x[j];
		ll dy = y[i]-y[j];
		ll dist = dx*dx+dy*dy;
		ll RR = (r[i]+r[j])*(r[i]+r[j]);
		return dist <= RR;
	};
	
	queue<int> q;
	vector<bool> vis(k);
	vector<vector<int>> con(k);
	
	for(int i = 0; i < k; i++) {
		if(x[i]-r[i]<=0 || y[i]+r[i]>=n)
			q.push(i);
		for(int j = i+1; j < k; j++) {
			if(touch(i, j)) {
				con[i].push_back(j);
				con[j].push_back(i);
			}
		}
	}
	while(!q.empty()) {
		auto curr = q.front();
		q.pop();
		if(vis[curr])
			continue;
		vis[curr] = true;
		for(int next : con[curr]) {
			if(!vis[next])
				q.push(next);
		}
	}
	bool win = false;
	for(int i = 0; i < k; i++) {
		if(x[i]+r[i]>=m || y[i]-r[i]<=0) {
			if(vis[i])
				win = true;
		}
	}
	if(win)
		cout << "N\n";
	else
		cout << "S\n";
	
}