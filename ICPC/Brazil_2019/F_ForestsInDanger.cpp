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

struct Node {
	ll val, lazy, cnt;
	Node(ll v=0, ll c=1) : val(v), lazy(0), cnt(c) {};
};

Node merge(Node a, Node b) {
	if(a.val == b.val)
		return Node(a.val, a.cnt+b.cnt);
	else if(a.val < b.val)
		return Node(a.val, a.cnt);
	else
		return Node(b.val, b.cnt);
}

void push(int index, vector<Node>& tree) {
	if(index*2 >= sz(tree)) {
		return;
	}
	tree[index*2].val += tree[index].lazy;
	tree[index*2].lazy += tree[index].lazy;
	tree[index*2+1].val += tree[index].lazy;
	tree[index*2+1].lazy += tree[index].lazy;
	tree[index].lazy = 0;
}

void update(int index, int currL, int currR, int left, int right, ll val, vector<Node>& tree) {
	if(currL > right || currR < left)
		return;

	if(left <= currL && currR <= right) {
		tree[index].val += val;
		tree[index].lazy += val;
		return;
	}
	push(index, tree);
	int mid = (currL+currR)/2;
	update(index*2, currL, mid, left, right, val, tree);
	update(index*2+1, mid+1, currR, left, right, val, tree);
	tree[index] = merge(tree[index*2], tree[index*2+1]);
}

void build(int index, int currL, int currR, vector<Node>& tree) {
	if(currL == currR) {
		tree[index].val = 0;
		tree[index].lazy = 0;
		tree[index].cnt = 1;
		return;
	}
	int mid = (currL+currR)/2;
	build(index*2, currL, mid, tree);
	build(index*2+1, mid+1, currR, tree);
	tree[index] = merge(tree[index*2], tree[index*2+1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<pair<pair<int, int>, int>> hor;
	vector<pair<pair<int, int>, int>> ver;
	for(int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if(x1 > x2)
			swap(x1, x2);
		if(y1 > y2)
			swap(y1, y2);
		if(x1 == x2)
			ver.push_back({{y1, y2}, x1});
		else
			hor.push_back({{x1, x2}, y1});
	}
	int p;
	cin >> p;
	int lox, loy, hix, hiy;
	cin >> lox >> loy >> hix >> hiy;
	ll area = (ll)(hix-lox)*(ll)(hiy-loy);
	int MX = hix-lox;
	
	auto clampX = [&](int x) {
		return max(lox, min(hix, x));
	};
	auto clampY = [&](int y) {
		return max(loy, min(hiy, y));
	};
	
	vector<Node> tree(MX*4);
	auto Query = [&]() {
		return tree[1];
	};
	auto Update = [&](int l, int r, ll val) {
		update(1, 0, MX-1, l-lox, r-lox, val, tree);
	};
	
	vector<vector<pair<int, pair<int, int>>>> events(1e5+2);
	auto check = [&](int r) {
		for(int i = 0; i < sz(events); i++)
			events[i].clear();
		for(auto& [range, x] : ver) {
			int lx = clampX(x-r);
			int hx = clampX(x+r);
			int ly = clampY(range.first-r);
			int hy = clampY(range.second+r);
			events[ly].push_back({1, {lx, hx-1}});
			events[hy].push_back({-1, {lx, hx-1}});
		}
		for(auto& [range, y] : hor) {
			int lx = clampX(range.first-r);
			int hx = clampX(range.second+r);
			int ly = clampY(y-r);
			int hy = clampY(y+r);
			events[ly].push_back({1, {lx, hx-1}});
			events[hy].push_back({-1, {lx, hx-1}});
		}
		
		ll tot = area;
		build(1, 0, MX-1, tree);
		for(int i = loy; i < hiy; i++) {
			for(auto [amt, range] : events[i]) {
				Update(range.first, range.second, amt);
			}
			auto res = Query();
			if(res.val == 0)
				tot -= res.cnt;
		}
		return area*p <= tot*100;
	};
	int l = 1, r = 1e5;
	while(l <= r) {
		int mid = (l+r)/2;
		if(check(mid))
			r = mid-1;
		else
			l = mid+1;
	}
	cout << l << "\n";
}