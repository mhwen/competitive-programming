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

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Node {
	ll val, lazy;
	Node(ll v=0) : val(v), lazy(0) {};
};

Node merge(Node a, Node b) {
	return Node(min(a.val, b.val));
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

void build(int index, int currL, int currR, vector<Node>& tree, vector<ll>& vals) {
	if(currL == currR) {
		tree[index].val = vals[currL];
		return;
	}
	int mid = (currL+currR)/2;
	build(index*2, currL, mid, tree, vals);
	build(index*2+1, mid+1, currR, tree, vals);
	tree[index] = merge(tree[index*2], tree[index*2+1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int& i : nums) {
			cin >> i;
			i--;
		}
		vector<ll> vals(n);
		iota(all(vals), 0LL);
		vector<Node> tree(4*n);
		build(1, 0, n-1, tree, vals);
		
		auto Query = [&]() {
			return tree[1].val;
		};
		auto Update = [&](int l, int r, ll val) {
			update(1, 0, n-1, l, r, val, tree);
		};
		
		vector<int> left(n);
		for(int i = 0; i < n; i++) {
			left[i] = nums[i];
			if(i > 0)
				left[i] = min(left[i-1], left[i]);
		}
		vector<int> right(n);
		for(int i = n-1; i >= 0; i--) {
			right[i] = nums[i];
			if(i < n-1)
				right[i] = min(right[i+1], right[i]);
			if(i > 0)
				Update(right[i], n-1, -1);
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(Query() >= 0)
				ans++;
			if(i < n-1)
				Update(right[i+1], n-1, 1);
			Update(left[i], n-1, -1);
		}
		cout << ans << "\n";
	}
}
