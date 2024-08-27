#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <fstream>

using namespace std;

typedef long long ll;
constexpr ll INF = 1e18;

struct node {
	ll count = 0;
	ll min = 0;
	ll lazy = 0;
	int size = 1;
};

void push(int curr, vector<node>& tree) {
	if(curr*2+2 >= (int)tree.size())
		return;
	tree[curr*2+1].count += tree[curr].lazy*tree[curr*2+1].size;
	tree[curr*2+1].min += tree[curr].lazy;
	tree[curr*2+1].lazy += tree[curr].lazy;
	tree[curr*2+2].count += tree[curr].lazy*tree[curr*2+2].size;
	tree[curr*2+2].min += tree[curr].lazy;
	tree[curr*2+2].lazy += tree[curr].lazy;
	tree[curr].lazy = 0;
}

void merge(int curr, vector<node>& tree) {
	if(curr*2+2 >= (int)tree.size())
		return;
	tree[curr].count = tree[curr*2+1].count+tree[curr*2+2].count;
	tree[curr].min = min(tree[curr*2+1].min, tree[curr*2+2].min);
	tree[curr].size = tree[curr*2+1].size+tree[curr*2+2].size;
}

void update(int curr, int currL, int currR, int l, int r, ll val, vector<node>& tree) {
	if(currR < l || currL > r)
		return;
	if(l <= currL && currR <= r) {
		tree[curr].count += tree[curr].size*val;
		tree[curr].min += val;
		tree[curr].lazy += val;
		return;
	}
	push(curr, tree);
	int mid = (currR+currL)/2;
	update(curr*2+1, currL, mid, l, r, val, tree);
	update(curr*2+2, mid+1, currR, l, r, val, tree);
	merge(curr, tree);
}

ll queryCount(int curr, int currL, int currR, int l, int r, vector<node>& tree) {
	if(currR < l || currL > r)
		return 0;
	if(l <= currL && currR <= r) {
		return tree[curr].count;
	}
	push(curr, tree);
	int mid = (currR+currL)/2;
	return queryCount(curr*2+1, currL, mid, l, r, tree) + queryCount(curr*2+2, mid+1, currR, l, r, tree);
}

ll queryMin(int curr, int currL, int currR, int l, int r, vector<node>& tree) {
	if(currR < l || currL > r)
		return INF;
	if(l <= currL && currR <= r) {
		return tree[curr].min;
	}
	push(curr, tree);
	int mid = (currR+currL)/2;
	return min(queryMin(curr*2+1, currL, mid, l, r, tree), queryMin(curr*2+2, mid+1, currR, l, r, tree));
}

void build(int curr, int currL, int currR, vector<node>& tree, vector<node>& vals) {
	if(currL == currR) {
		tree[curr] = vals[currL];
		return;
	}
	int mid = (currL+currR)/2;
	build(curr*2+1, currL, mid, tree, vals);
	build(curr*2+2, mid+1, currR, tree, vals);
	merge(curr, tree);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("haybales.in");
	ofstream cout("haybales.out");
	int n, q;
	cin >> n >> q;
	vector<node> tree(4*n);
	vector<node> nodes(n);
	for(int i = 0; i < n; i++) {
		ll a;
		cin >> a;
		nodes[i].count = nodes[i].min = a;
	}
	build(0, 0, n-1, tree, nodes);
	while(q-->0) {
		char type;
		cin >> type;
		if(type == 'M') {
			int a, b;
			cin >> a >> b;
			cout << queryMin(0, 0, n-1, a-1, b-1, tree) << "\n";
		}
		else if(type == 'P') {
			int a, b;
			ll c;
			cin >> a >> b >> c;
			update(0, 0, n-1, a-1, b-1, c, tree);
		}
		else {
			int a, b;
			cin >> a >> b;
			cout << queryCount(0, 0, n-1, a-1, b-1, tree) << "\n";
		}
		
	}
}