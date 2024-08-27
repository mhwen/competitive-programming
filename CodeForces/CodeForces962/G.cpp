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

constexpr int INF = 1e9;

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

struct Node {
	int val, count, lazy;
	Node(int v=0, int c=1, int l=0) : val(v), count(c), lazy(l) {}
};

Node merge(Node a, Node b) {
	if(a.val == b.val)
		return Node(a.val, a.count+b.count, 0);
	if(a.val > b.val)
		swap(a, b);
	return Node(a.val, a.count, 0);
}

void add(Node& a, int val) {
	a.val += val;
	a.lazy += val;
}

void push(int p, vector<Node>& tree) {
	if(p*2+1 >= sz(tree))
		return;
	Node curr = tree[p];
	add(tree[p*2], curr.lazy);
	add(tree[p*2+1], curr.lazy);
	tree[p] = merge(tree[p*2], tree[p*2+1]);
}


void update(int curr, int l, int r, int L, int R, int val, vector<Node>& tree) {
	if(r < L || l > R)
		return;
	if(L <= l && r <= R) {
		add(tree[curr], val);
		return;
	}
	int mid = (l+r)/2;
	push(curr, tree);
	update(curr*2, l, mid, L, R, val, tree);
	update(curr*2+1, mid+1, r, L, R, val, tree);
	tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
}

Node query(int curr, int l, int r, int L, int R, vector<Node>& tree) {
	if(r < L || l > R)
		return Node(INF, 0, 0);
	if(L <= l && r <= R)
		return tree[curr];
	push(curr, tree);
	int mid = (l+r)/2;
	auto left = query(curr*2, l, mid, L, R, tree);
	auto right = query(curr*2+1, mid+1, r, L, R, tree);
	return merge(left, right);
}

void build(int curr, int l, int r, vector<Node>& tree) {
	if(l == r) return;
	int mid = (l+r)/2;
	build(curr*2, l, mid, tree);
	build(curr*2+1, mid+1, r, tree);
	tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> next(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			next[a].push_back(b);
			next[b].push_back(a);
		}
		vector<Node> tree(4*n);
		build(1, 0, n-1, tree);
		function<void(int, int, int)> Update = [&](int L, int R, int val) {
			if(L > R) {
				Update(L, n-1, val);
				Update(0, R, val);
				return;
			}
			update(1, 0, n-1, L, R, val, tree);
		};
		
		auto Query = [&] {
			auto res = query(1, 0, n-1, 0, n-1, tree);
			if(res.val == 0)
				return n-res.count;
			else
				return n;
		};
		
		for(int start = 0; start < n; start++) {
			for(int end : next[start])
				if(start < end)
					Update(start, end-1, 1);
		}
		int ans = Query();
		for(int start = 0; start < n; start++) {
			for(int end : next[start]) {
				Update(start, (end-1+n)%n, -1);
				Update(end, (start-1+n)%n, 1);
			}
			ans = min(ans, Query());
		}
		cout << ans << "\n";
	}
	
}