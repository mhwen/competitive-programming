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

struct Node {
	int val = 0;
	Node* left;
	Node* right;
};

int queryNode(Node* node, int l, int r, int currL, int currR) {
	if(r < currL || l > currR)
		return 0;
	if(l <= currL && currR <= r)
		return node->val;
	
	int res = 0;
	int mid = (currL+currR)/2;
	
	if(node->left != NULL) {
		res += queryNode(node->left, l, r, currL, mid);
	}
	if(node->right != NULL) {
		res += queryNode(node->right, l, r, mid+1, currR);
	}
	return res;
}

void updateNode(Node* node, int p, int currL, int currR, int val) {
	if(p < currL || p > currR)
		return;
	node->val += val;
	if(currL == currR)
		return;
	int mid = (currL+currR)/2;
	

	if(p <= mid) {
		if(node->left == NULL) {
			node->left = new Node();
		}
		updateNode(node->left, p, currL, mid, val);
	}
	else {
		if(node->right == NULL) {
			node->right = new Node();
		}	
		updateNode(node->right, p, mid+1, currR, val);
	}

}

ll query(int l, int r, int t1, int t2, vector<Node>& tree) {
	if(t2 < t1)
		return 0;
	ll res = 0;
	for(int t = t2; t >= 0; t = (t&(t+1))-1) {
		res += queryNode(&tree[t], l, r, 1, 1e9);
	}
	for(int t = t1-1; t >= 0; t = (t&(t+1))-1) {
		res -= queryNode(&tree[t], l, r, 1, 1e9);
	}
	return res;
}

void update(int p, int val, int t, vector<Node>& tree) {
	int n = (int)tree.size();
	for(; t < n; t = t|(t+1)) {
		updateNode(&tree[t], p, 1, 1e9, val);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("mowing.in");
	ofstream cout("mowing.out");
	int n, t;
	cin >> n >> t;
	vector<int> x(n);
	vector<int> y(n);
	for(int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	//x, y, time, type
	vector<tuple<int, int, int, int>> horizontals;
	//x, y1, y2, time
	vector<tuple<int, int, int, int>> verticals;
	for(int i = 0; i < n-1; i++) {
		if(x[i] == x[i+1]) {
			int y1 = y[i];
			int y2 = y[i+1];
			if(y1 > y2)
				swap(y1, y2);
			if(y2-y1 > 1)
				verticals.push_back({x[i], y1+1, y2-1, i});
		}
		else {
			int x1 = x[i];
			int x2 = x[i+1];
			if(x1 > x2)
				swap(x1, x2);
			if(x2-x1 > 1) {
				horizontals.push_back({x1+1, y[i], i, 1});
				horizontals.push_back({x2, y[i], i, -1});
			}
		}
	}
	sort(horizontals.begin(), horizontals.end());
	sort(verticals.begin(), verticals.end());
	int hId = 0, vId = 0;
	ll ans = 0;
	
	vector<Node> tree(n);
	
	
	while(hId < (int)horizontals.size() && vId < (int)verticals.size()) {
		auto [hx, hy, htime, htype] = horizontals[hId];
		auto [vx, vy1, vy2, vtime] = verticals[vId];
		if(hx <= vx) {
			update(hy, htype, htime, tree);
			hId++;
		}
		else {
			ans += query(vy1, vy2 , 0, vtime-t, tree);
			ans += query(vy1, vy2, vtime+t, n-1, tree);
			vId++;
		}
	}
	
	while(vId < (int)verticals.size()) {
		//process remaining verticals
		auto [vx, vy1, vy2, vtime] = verticals[vId];
		ans += query(vy1, vy2 , 0, vtime-t, tree);
		ans += query(vy1, vy2, vtime+t, n-1, tree);
		vId++;
	}
	
	cout << ans << "\n";
}