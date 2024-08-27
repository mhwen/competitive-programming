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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
		}
		vector<int> vals(n);
		for(int i = 0; i < n; i++) {
			cin >> vals[i];
		}
		vector<int> dep(n);
		vector<vector<int>> par(30, vector<int>(n));
		function<void(int, int, int)> dfs = [&](int curr, int prev, int d) { 
			dep[curr] = d;
			par[0][curr] = prev;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, d+1);
			}
		};
		dfs(0, 0, 0);
		
		for(int bit = 1; bit < 30; bit++) {
			for(int i = 0; i < n; i++) {
				par[bit][i] = par[bit-1][par[bit-1][i]];
			}
		}
		
		auto lca = [&](int a, int b) {
			if(dep[a] < dep[b])
				swap(a, b);
			for(int bit = 29; bit >= 0; bit--) {
				if(dep[a]-dep[b] >= (1<<bit))
					a = par[bit][a];
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
		
		auto getAns = [&](int a, int b) {
			int l = lca(a, b);

			int pLen = dep[a]+dep[b]-2*dep[l]+1;
			if(pLen > 2001)
				return 0;
			vector<int> nums(2001);
			while(a != l) {
				nums[vals[a]]++;
				if(nums[vals[a]] > 1)
					return 0;
				a = par[0][a];
			}
			while(b != l) {
				nums[vals[b]]++;
				if(nums[vals[b]] > 1)
					return 0;
				b = par[0][b];
			}
			nums[vals[l]]++;
			if(nums[vals[l]] > 1)
				return 0;
			vector<int> mm;
			for(int i = 0; i <= 2000; i++) {
				if(nums[i] > 0)
					mm.push_back(i);
			}
			int best = 1e9;
			for(int i = 0; i < sz(mm)-1; i++) {
				best = min(best, (mm[i]^mm[i+1])/2);
			}
			return best;
		};
		
		while(q-->0) {
			int type, a, b;
			cin >> type >> a >> b;
			if(type == 1) {
				a--;
				vals[a] = b;
			}
			else {
				a--; b--;
				cout << getAns(a, b) << "\n";
			}
		}
	}
}