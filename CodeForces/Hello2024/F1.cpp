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

struct Node {
	ll extraWater = 0;
	ll need = 0;
	Node() : extraWater(0), need(0) {}
	Node(ll e, ll n) : extraWater(e), need(n) {}
};

Node merge(Node a, Node b) {
	ll newNeed = a.need;
	ll newWater = b.extraWater;
	if(a.extraWater >= b.need)
		newWater += a.extraWater-b.need;
	else
		newNeed += b.need-a.extraWater;
	return Node(newWater, newNeed);
}

void update(int curr, int li, int ri, int p, ll newW, ll newN, vector<Node>& tree) {
	if(li > p || ri < p)
		return;
	if(li == ri) {
		tree[curr].extraWater = newW;
		tree[curr].need = newN;
		return;
	}
	int mid = (li+ri)/2;
	update(curr*2, li, mid, p, newW, newN, tree);
	update(curr*2+1, mid+1, ri, p, newW, newN, tree);
	tree[curr] = merge(tree[curr*2], tree[curr*2+1]);
}

Node query(int curr, int li, int ri, int p, vector<Node>& tree) {
	if(li == ri)
		return tree[curr];
	int mid = (li+ri)/2;
	if(p <= mid)
		return query(curr*2, li, mid, p, tree);
	else
		return query(curr*2+1, mid+1, ri, p, tree);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<ll> water(n);
	vector<ll> need(n);
	ll totalWater = 0;
	for(int i = 0; i < n; i++) {
		cin >> water[i];
		totalWater += water[i];
	}
	for(int i = 0; i < n; i++) {
		cin >> need[i];
	}
	vector<ll> cap(n);
	for(int i = 0; i < n-1; i++) {
		cin >> cap[i];
	}
	vector<Node> tree(4*n);
	for(int i = 0; i < n; i++) {
		update(1, 0, n-1, i, max(0LL, water[i]-need[i]), max(0LL, need[i]-water[i]), tree);
	}
	while(q-->0) {
		int p;
		ll x, y, z;
		cin >> p >> x >> y >> z;
		p--;
		totalWater += x-water[p];
		water[p] = x;
		need[p] = y;
		ll extraWater = max(0LL, water[p]-need[p]);
		ll newNeed = max(0LL, need[p]-water[p]);
		update(1, 0, n-1, p, extraWater, newNeed, tree);
		cout << totalWater - tree[1].extraWater << "\n";
	}

	
}