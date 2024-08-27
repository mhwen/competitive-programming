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
	int val = 0;
	int lazy = 0;
};

void add(Node& node, int addVal) {
	node.val += addVal;
	node.lazy += addVal;
};

void push(int index, vector<Node>& tree) {
	add(tree[index*2], tree[index].lazy);
	add(tree[index*2+1], tree[index].lazy);
	tree[index].lazy = 0;
}

void merge(int index, vector<Node>& tree) {
	Node curr = tree[index];
	Node left = tree[index*2];
	Node right = tree[index*2+1];
	curr.val = max(left.val, right.val);
	tree[index] = curr;
}

void update(int index, int li, int ri, int left, int right, int val, vector<Node>& tree) {
	if(li > right || ri < left)
		return;
	if(left <= li && ri <= right) {
		add(tree[index], val);
		return;
	}
	push(index, tree);
	int mid = (li+ri)/2;
	update(index*2, li, mid, left, right, val, tree);
	update(index*2+1, mid+1, ri, left, right, val, tree);
	merge(index, tree);
}

int query(int index, int li, int ri, int left, int right, vector<Node>& tree) {
	if(li > right || ri < left)
		return 0;
	if(left <= li && ri <= right)
		return tree[index].val;
	push(index, tree);
	int mid = (li+ri)/2;
	return max(query(index*2, li, mid, left, right, tree),
			query(index*2+1, mid+1, ri, left, right, tree));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> children(n);
		vector<int> par(n);
		for(int i = 1; i < n; i++) {
			int p;
			cin >> p;
			p--;
			par[i] = p;
			children[p].push_back(i);
		}
		vector<int> colors(n);
		for(int i = 0; i < n; i++) {
			cin >> colors[i];
			colors[i]--;
		}
		vector<vector<int>> nextColors(n);
		vector<int> prevColor(n, -1);
		vector<Node> tree(4*n);
		vector<int> entry(n);
		vector<int> exit(n);
		int treeId = 0;
		function<void(int)> dfs = [&](int curr) {
			entry[curr] = treeId++;
			int currColor = colors[curr];
			int prevCId = prevColor[currColor];
			int added = 0;
			if(prevCId != -1) {
				nextColors[prevCId].push_back(curr);
			}
			else {
				added = 1;
			}
			prevColor[currColor] = curr;
			
			for(int next : children[curr]) {
				dfs(next);
			}
			prevColor[currColor] = prevCId;
			exit[curr] = treeId-1;
			
			update(1, 0, n-1, entry[curr], exit[curr], added, tree);
		};
		dfs(0);
		// cout << "treeid " << treeId << "\n";
		// for(int i = 0; i < n; i++) {
			// cout << i+1 << " " << query(1, 0, 2*n-1, entry[i], exit[i], tree) << endl;
		// }
		ll ans = query(1, 0, n-1, entry[0], exit[0], tree);
		function<void(int)> dfs2 = [&](int curr) {
			vector<ll> sizes;
			for(int next : children[curr]) {
				sizes.push_back(query(1, 0, n-1, entry[next], exit[next], tree));
			}
			sort(sizes.rbegin(), sizes.rend());
			if((int)sizes.size() > 1) {
				ans = max(ans, sizes[0]*sizes[1]);
			}
			update(1, 0, n-1, entry[curr], exit[curr], -1, tree);
			for(int activate: nextColors[curr]) {
				update(1, 0, n-1, entry[activate], exit[activate], 1, tree);
			}
			for(int next : children[curr]) {
				dfs2(next);
			}
			for(int activate: nextColors[curr]) {
				update(1, 0, n-1, entry[activate], exit[activate], -1, tree);
			}
		};
		
		dfs2(0);
		cout << ans << "\n";

	}
}