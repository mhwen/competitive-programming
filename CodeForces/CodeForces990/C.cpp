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

struct segtree {
	int n;
	vector<int> tree;

	segtree(int _n) : n(_n), tree(2*n) {}
	void update(int p, int val) {
		p += n;
		while(p > 0) {
			tree[p] += val;
			p/=2;
		}
	}
	int query(int l, int r) {
		l += n; r += n;
		int res = 0;
		while(l<=r) {
			if(l%2==1)
				res += tree[l++];
			if(r%2==0)
				res += tree[r--];
			l/=2; r/=2;
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> x(n);
		vector<int> y(n);
		set<int> xCord;
		set<int> yCord;
		for(int i = 0; i < n; i++) {
			cin >> x[i] >> y[i];
			xCord.insert(x[i]);
			yCord.insert(y[i]);
		}
		map<int, int> xRealToId;
		map<int, int> yRealToId;
		vector<int> xIdToReal(sz(xCord));
		vector<int> yIdToReal(sz(yCord));
		int xId = 0;
		for(auto a : xCord) {
			xRealToId[a] = xId;
			xIdToReal[xId] = a;
			xId++;
		}
		int yId = 0;
		for(auto a : yCord) {
			yRealToId[a] = yId;
			yIdToReal[yId] = a;
			yId++;
		}
		vector<vector<int>> events(xId);
		segtree left(yId);
		segtree right(yId);
		for(int i = 0; i < n; i++) {
			x[i] = xRealToId[x[i]];
			y[i] = yRealToId[y[i]];
			events[x[i]].push_back(y[i]);
			left.update(y[i], 1);
		}
		int best = 0;
		pair<int, int> ans{0, 0};
		
		auto check = [&](int XX, int YY) {
			int pos = YY;
			if(pos < 0 || pos >= yId)
				return;
			int tr = right.query(pos, yId-1);
			int br = right.query(0, pos-1);
			int tl = left.query(pos, yId-1);
			int bl = left.query(0, pos-1);
			int res = min(min(tr, br), min(tl, bl));
			if(res > best) {
				best = res;
				ans = {xIdToReal[XX], yIdToReal[YY]};
			}
		};
		
		auto search = [&]() {
			int l = 0, r = yId-1;
			while(l <= r) {
				int pos = (l+r)/2;
				int tr = right.query(pos, yId-1);
				int br = right.query(0, pos-1);
				int tl = left.query(pos, yId-1);
				int bl = left.query(0, pos-1);
				int small = min(min(tr, br), min(tl, bl));
				if(tr == small || tl == small)
					r = pos-1;
				else
					l = pos+1;
			}
			return r;
		};
		
		for(int i = xId-1; i >= 0; i--) {
			for(auto Y : events[i]) {
				left.update(Y, -1);
				right.update(Y, 1);
			}
			int id = search();
			for(int d = -2; d <= 2; d++)
				check(i, id+d);
		}
		cout << best << "\n";
		cout << ans.first << " " << ans.second << "\n";
	}
}