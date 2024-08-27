#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

struct Node {
	ll x, c, d;
	Node() : x(1), c(0), d(1) {}
	Node(ll X, ll C, ll D) : x(X), c(C), d(D) {}

};

Node apply(Node outer, Node inner) {
	ll newD = outer.d*inner.d%MOD;
	ll newX = outer.x*inner.x%MOD;
	ll newC = (outer.x*inner.c%MOD + outer.c*inner.d%MOD)%MOD;
	return Node(newX, newC, newD);
}

void push(int p, vector<Node>& tree) {
	tree[p*2] = apply(tree[p], tree[p*2]);
	tree[p*2+1] = apply(tree[p], tree[p*2+1]);
	tree[p] = Node();
}

void update(int p, int li, int ri, int left, int right, Node fun, vector<Node>& tree) {
	if(ri < left || right < li)
		return;
	if(left <= li && ri <= right) {
		tree[p] = apply(fun, tree[p]);
		return;
	}
	int mid = (li+ri)/2;
	push(p, tree);
	update(p*2, li, mid, left, right, fun, tree);
	update(p*2+1, mid+1, ri, left, right, fun, tree);
}

Node query(int p, int li, int ri, int target, vector<Node>& tree) {
	if(li == ri)
		return tree[p];
	push(p, tree);
	int mid = (li+ri)/2;
	if(target <= mid)
		return query(p*2, li, mid, target, tree);
	else
		return query(p*2+1, mid+1, ri, target, tree);
}

ll pow(ll a, ll b) {
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	
	vector<Node> tree(4*n);	
	for(int i = 0; i < m; i++) {
		int l, r;
		ll x;
		cin >> l >> r >> x;
		l--; r--;
		ll width = r-l+1;
		Node fun(width-1, x, width);
		update(1, 0, n-1, l, r, fun, tree);
	}
	for(int i = 0; i < n; i++) {
		Node fun = query(1, 0, n-1, i, tree);
		cout << (fun.x*nums[i]%MOD + fun.c)%MOD*inv(fun.d)%MOD << " ";
	}
	cout << "\n";
}