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

void push(int curr, vector<int>& tree, vector<int>& lazy) {
	if(curr*2+1 >= (int)tree.size())
		return;
	tree[curr*2+1] += lazy[curr];
	tree[curr*2+2] += lazy[curr];
	lazy[curr*2+1] += lazy[curr];
	lazy[curr*2+2] += lazy[curr];
	lazy[curr] = 0;
}

void update(int curr, int l, int r, int left, int right, int val, vector<int>& tree, vector<int>& lazy) {
	if(r < left || l > right)
		return;
	if(left <= l && r <= right) {
		tree[curr] += val;
		lazy[curr] += val;
		return;
	}
	push(curr, tree, lazy);
	int mid = (l+r)/2;
	update(curr*2+1, l, mid, left, right, val, tree, lazy);
	update(curr*2+2, mid+1, r, left, right, val, tree, lazy);
	tree[curr] = min(tree[curr*2+1], tree[curr*2+2]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("cardgame.in");
	ofstream cout("cardgame.out");
	int n;
	cin >> n;
	vector<int> order(n);
	vector<bool> taken(2*n);
	for(int i = 0; i < n; i++) {
		cin >> order[i];
		order[i]--;
		taken[order[i]] = true;
	}
	vector<int> mine;
	for(int i = 2*n-1; i >= 0; i--) {
		if(!taken[i])
			mine.push_back(i);
	}
	vector<int> leftBest(n+1);
	vector<int> leftTree(8*n);
	vector<int> leftLazy(8*n);
	for(int i = 0; i < n; i++) {
		update(0, 0, 2*n-1, 0, order[i], -1, leftTree, leftLazy);
		update(0, 0, 2*n-1, 0, mine[i], 1, leftTree, leftLazy);
		leftBest[i+1] = i+1+leftTree[0];
	}
	vector<int> rightBest(n+1);
	vector<int> rightTree(8*n);
	vector<int> rightLazy(8*n);
	for(int i = n-1; i >= 0; i--) {
		update(0, 0, 2*n-1, order[i], 2*n-1, -1, rightTree, rightLazy);
		update(0, 0, 2*n-1, mine[i], 2*n-1, 1, rightTree, rightLazy);
		rightBest[n-i] = n-i+rightTree[0];
	}
	int ans = 0;
	for(int i = 0; i <= n; i++) {
		ans = max(ans, leftBest[i]+rightBest[n-i]);
	}
	cout << ans << "\n";
	
}