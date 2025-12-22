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

struct M {
	int a, b, c;
	M(): a(-1), b(-1), c(-1) {}
	M(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<pair<int, int>> e;
		vector<set<int>> con(n);
		for(int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].insert(v);
			con[v].insert(u);
			e.push_back({u+1, v+1});
		}
		vector<M> ans;
		queue<int> q;
		for(int i = 0; i < n; i++)
			if(sz(con[i]) > 1)
				q.push(i);
		
		while(!q.empty()) {
			int curr = q.front();
			q.pop();
			if(sz(con[curr]) <= 1)
				continue;
			int a = *con[curr].begin();
			con[curr].erase(a);
			con[a].erase(curr);
			int b = *con[curr].begin();
			con[curr].erase(b);
			con[b].erase(curr);
			assert(a != b);
			ans.push_back(M(curr, a, b));
			if(con[a].count(b)) {
				assert(con[b].count(a));
				con[a].erase(b);
				con[b].erase(a);
			}
			else {
				assert(!con[b].count(a));
				con[a].insert(b);
				con[b].insert(a);
				if(sz(con[a]) > 1)
					q.push(a);
				if(sz(con[b]) > 1)
					q.push(b);
			}
			if(sz(con[curr]) > 1)
				q.push(curr);
		}
		
		vector<int> currComp;
		vector<bool> vis(n);
		vector<vector<int>> comps;
		function<void(int)> flood = [&](int curr) {
			if(vis[curr])
				return;
			vis[curr] = true;
			currComp.push_back(curr);
			for(auto next : con[curr]) {
				flood(next);
			}
		};
		
		for(int i = 0; i < n; i++) {
			if(vis[i])
				continue;
			currComp.clear();
			flood(i);
			comps.push_back(currComp);
		}
		
		for(int i = 0; i < sz(comps); i++) {
			if(sz(comps[i]) > sz(comps[0])) {
				swap(comps[0], comps[i]);
				break;
			}
		}
		if(sz(comps[0]) > 1) {
			int p = comps[0][0];
			int Q = comps[0][1];
			for(int i = 1; i < sz(comps); i++) {
				int r = comps[i].front();
				ans.push_back(M(p, Q, r));
				Q = r;
			}
		}
		assert(sz(ans) <= 2*max(n, m));
		cout << sz(ans) << "\n";
		for(M mm : ans) {
			cout << mm.a+1 << " " << mm.b+1 << " " << mm.c+1 << "\n";
		}
	}
}