#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int query(int l, int r, int val, vector<vector<int>>& tree) {
	int n = (int)tree.size()/2;
	l += n; r += n;
	int best = n;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			auto it = lower_bound(tree[l].begin(), tree[l].end(), val);
			if(it != tree[l].end())
				best = min(best, *it);
			l++;
		}
		if(r%2==0) {
			auto it = lower_bound(tree[r].begin(), tree[r].end(), val);
			if(it != tree[r].end())
				best = min(best, *it);
			r--;
		}
	}
	return best;
}

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
		vector<int> pos(n);
		for(int i = 0; i < n; i++) {
			int p;
			cin >> p;
			p--;
			pos[p] = i;
		}
		vector<int> in(n);
		vector<int> out(n);
		vector<vector<int>> tree(4*n);
		
		vector<int> order;
		int id = 0;
		auto dfs = [&](auto self, int curr, int prev) -> void {
			order.push_back(curr);
			in[curr] = id++;
			for(int next : con[curr]) {
				if(next != prev)
					self(self, next, curr);
			}
			order.push_back(curr);
			out[curr] = id++;
		};
		
		dfs(dfs, 0, -1);
		
		for(int i = 0; i < (int)order.size(); i++) {
			if(i == in[order[i]])
				tree[i+2*n].push_back(pos[order[i]]);
		}
		for(int i = 2*n-1; i > 0; i--) {
			tree[i].resize(tree[i*2].size()+tree[i*2+1].size());
			merge(tree[i*2].begin(), tree[i*2].end(), tree[i*2+1].begin(), tree[i*2+1].end(), tree[i].begin());
		}
		
		while(q-->0) {
			int l, r, x;
			cin >> l >> r >> x;
			l--; r--; x--;
			int res = query(in[x], out[x], l, tree);
			if(res <= r)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
		cout << "\n";
	}
}