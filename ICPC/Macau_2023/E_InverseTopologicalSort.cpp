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

void update(int p, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	p += n;
	while(p > 0) {
		tree[p] = val;
		p >>= 1;
	}
}

int query(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	int mx = -1;
	l+=n; r+=n;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			mx = max(mx, tree[l]);
			l++;
		}
		if(r%2==0) {
			mx = max(mx, tree[r]);
			r--;
		}
	}
	return mx;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> b(n);
	vector<int> atree(2*n, -1);
	vector<int> btree(2*n, -1);
	set<pair<int, int>> edges;
	vector<vector<int>> con(n);
	vector<int> degree(n);
	
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		int res = query(a[i], n-1, atree);
		if(res != -1) {
			int from = a[res];
			edges.insert({from, a[i]});
			con[from].push_back(a[i]);
			degree[a[i]]++;
		}
		update(a[i], i, atree);
	}
	for(int i = 0; i < n; i++) {
		cin >> b[i];
		b[i]--;
		int res = query(0, b[i], btree);
		if(res != -1) {
			int from = b[res];
			edges.insert({from, b[i]});
			con[from].push_back(b[i]);
			degree[b[i]]++;
		}
		update(b[i], i, btree);
	}
	
		

	// for(int i = 0; i < n-1; i++) {
		// if(bid[a[i]] < bid[a[i+1]]) {
			// con[a[i]].push_back(a[i+1]);
			// edges.insert({a[i], a[i+1]});
			// degree[a[i+1]]++;
		// }
		// if(aid[b[i]] < aid[b[i+1]]) {
			// con[b[i]].push_back(b[i+1]);
			// edges.insert({b[i], b[i+1]});
			// degree[b[i+1]]++;
		// }
	// }
	
	function<vector<int>(bool)> topo = [&](bool small) {
		vector<int> deg = degree;
		
		auto cmp = [small](int i, int j) -> bool {
			if (small) {
				return i < j;
			} else {
				return i > j;
			}
		};
		priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
		
		for(int i = 0; i < n; i++) {
			if(deg[i] == 0)
				q.push(i);
		}
		vector<int> order;
		vector<bool> vis(n);
		while(!q.empty()) {
			int curr = q.top();
			q.pop();
			order.push_back(curr);
			if(vis[curr])
				return vector<int>();
			vis[curr] = true;
			for(int next : con[curr]) {
				deg[next]--;
				if(deg[next] == 0)
					q.push(next);
			}
		}
		return order;
	};
	
	auto small = topo(false);
	auto big = topo(true);
	// for(int s : small)
		// cout << s << " ";
	// cout << endl;
	// for(int s : big)
		// cout << s << " ";
	// cout << endl;
	// for(auto e : edges)
			// cout << e.first+1 << " " << e.second+1 << "\n";
	if(small != a || big != b)
		cout << "No\n";
	else {
		cout << "Yes\n";
		cout << edges.size() << "\n";
		for(auto e : edges)
			cout << e.first+1 << " " << e.second+1 << "\n";
	}

}