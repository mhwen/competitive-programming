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

struct Slope {
	int x, y;
	Slope(int _x, int _y) {
		int g = gcd(_x, _y);
		x = _x/g;
		y = _y/g;
	}
	bool operator<(Slope s) const {
		return tie(x, y) < tie(s.x, s.y);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	map<Slope, queue<int>> seen;
	vector<vector<Slope>> slopes(n);
	for(int i = 0; i < n; i++) {
		int k;
		cin >> k;
		vector<int> x(k);
		vector<int> y(k);
		for(int j = 0; j < k; j++)
			cin >> x[j] >> y[j];
		for(int j = 0; j < k; j++) {
			int nxt = (j+1)%k;
			Slope s = Slope(x[nxt]-x[j], y[nxt]-y[j]);
			seen[s].push(i);
			slopes[i].push_back(s);
		}
	}
	int q;
	cin >> q;
	vector<pair<int, int>> queries(q);
	for(int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		queries[i] = {l, r};
	}
	vector<int> order(q);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		return queries[a].first < queries[b].first;
	});
	vector<int> tree(2*n);
	auto query = [&](int l, int r) {
		int res = 0;
		l+=n; r+=n;
		while(l<=r) {
			if(l%2==1)
				res += tree[l++];
			if(r%2==0)
				res += tree[r--];
			l/=2;
			r/=2;
		}
		return res;
	};
	auto update = [&](int p, int val) {
		p+=n;
		while(p>0) {
			tree[p] += val;
			p/=2;
		}
	};
	for(auto& [s, qu] : seen)
		update(qu.front(), 1);
	vector<int> ans(q);
	int prev = 0;
	for(int id : order) {
		auto [l, r] = queries[id];
		while(prev < l) {
			for(auto s : slopes[prev]) {
				update(seen[s].front(), -1);
				seen[s].pop();
				if(!seen[s].empty())
					update(seen[s].front(), 1);
			}
			prev++;
		}
		ans[id] = query(l, r);
	}
	for(int i : ans)
		cout << i << "\n";
}