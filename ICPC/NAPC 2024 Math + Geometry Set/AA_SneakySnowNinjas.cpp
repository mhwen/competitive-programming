#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

ll d2(ll x1, ll y1, ll x2, ll y2) {
	ll dx = x2-x1;
	ll dy = y2-y1;
	return dx*dx+dy*dy;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<set<pair<ll, int>>> p(60005);
		vector<ll> x(n+1);
		vector<ll> y(n+1);
		for(int i = 1; i <= n; i++) {
			cin >> x[i] >> y[i];
			x[i]+=30000;
			p[x[i]].insert({y[i], i});	
		}
		x[0] = 30000;
		p[x[0]].insert({y[0], 0});
		
		ll best = 0;
		vector<bool> vis(n+1);
		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int curr = q.front();
			q.pop();
			if(vis[curr])
				continue;
			vis[curr] = true;
			ll currX = x[curr];
			ll currY = y[curr];
			best = max(best, d2(currX, currY, x[0], y[0]));
			p[currX].erase({currY, curr});
			for(int offset = -100; offset <= 100; offset++) {
				ll newX = currX+offset;
				if(newX < 0 || newX >= sz(p) || p[newX].empty())
					continue;
				auto it = p[newX].upper_bound({currY, curr});
				if(it != p[newX].end()) {
					if(d2(currX, currY, newX, it->first) <= 10000)
						q.push({it->second});
				}
				if(it != p[newX].begin()) {
					it--;
					if(d2(currX, currY, newX, it->first) <= 10000)
						q.push({it->second});
				}
			}
		}
		cout << (ll)sqrt(best) << "\n";
	}
}