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
	ll val = 0;
	ll size = 1;
	ll set = 0;
	bool isSet = false;
};

void setNode(Node& node, ll setVal) {
	node.isSet = true;
	node.set = setVal;
	node.val = node.size*setVal;
}

void push(int index, vector<Node>& tree) {
	if(tree[index].isSet) {
		setNode(tree[index*2], tree[index].set);
		setNode(tree[index*2+1], tree[index].set);
	}
	tree[index].isSet = false;
}

void merge(int index, vector<Node>& tree) {
	Node curr = tree[index];
	Node left = tree[index*2];
	Node right = tree[index*2+1];
	curr.val = left.val+right.val;
	curr.size = left.size+right.size;
	tree[index] = curr;
}

void updateSet(int index, int currL, int currR, int left, int right, ll setVal, vector<Node>& tree) {
	if(left > right)
		return;
	if(currL > right || currR < left)
		return;

	if(left <= currL && currR <= right) {
		setNode(tree[index], setVal);
		return;
	}
	
	push(index, tree);
	int mid = (currL+currR)/2;
	updateSet(index*2, currL, mid, left, right, setVal, tree);
	updateSet(index*2+1, mid+1, currR, left, right, setVal, tree);
	merge(index, tree);
}

ll query(int index, int currL, int currR, int left, int right, vector<Node>& tree) {
	if(currL > right || currR < left)
		return 0;
	if(left <= currL && currR <= right)
		return tree[index].val;
	push(index, tree);
	int mid = (currL+currR)/2;
	return query(index*2, currL, mid, left, right, tree)+
			query(index*2+1, mid+1, currR, left, right, tree);
}

void build(int index, int currL, int currR, vector<Node>& tree, vector<Node>& vals) {
	if(currL == currR) {
		tree[index] = vals[currL];
		return;
	}
	int mid = (currL+currR)/2;
	build(index*2, currL, mid, tree, vals);
	build(index*2+1, mid+1, currR, tree, vals);
	merge(index, tree);
}

void updateMax(int curr, int pos, int currL, int currR, ll val, vector<ll>& tree) {
	if(pos > currR || pos < currL)
		return;
	if(currL == currR) {
		tree[curr] = val;
		return;
	}
	int mid = (currL+currR)/2;
	updateMax(curr*2, pos, currL, mid, val, tree);
	updateMax(curr*2+1, pos, mid+1, currR, val, tree);
	tree[curr] = max(tree[curr*2], tree[curr*2+1]);
}

int queryNextGreaterLeft(int curr, int currL, int currR, int maxId, ll threshold, vector<ll>& tree) {
	if(tree[curr] < threshold || currL >= maxId)
		return -1;
	if(currL == currR)
		return currL;
	int mid = (currL+currR)/2;
	int rightQ = queryNextGreaterLeft(curr*2+1, mid+1, currR, maxId, threshold, tree);
	if(rightQ != -1)
		return rightQ;
	return queryNextGreaterLeft(curr*2, currL, mid, maxId, threshold, tree);
}

int queryNextGreaterRight(int curr, int currL, int currR, int maxId, ll threshold, vector<ll>& tree) {
	if(tree[curr] < threshold || currR <= maxId)
		return -1;
	if(currL == currR)
		return currL;
	int mid = (currL+currR)/2;
	int leftQ = queryNextGreaterRight(curr*2, currL, mid, maxId, threshold, tree);
	if(leftQ != -1)
		return leftQ;
	return queryNextGreaterRight(curr*2+1, mid+1, currR, maxId, threshold, tree);
}


ll queryMax(int curr, int currL, int currR, int left, int right, vector<ll>& tree) {
	if(currL > right || currR < left)
		return -1;
	if(left <= currL && currR <= right)
		return tree[curr];
	int mid = (currL+currR)/2;
	return max(queryMax(curr*2, currL, mid, left, right, tree),
			   queryMax(curr*2+1, mid+1, currR, left, right, tree));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	n+=2;
	vector<ll> heights(n);
	ll totalHeight = 0;
	vector<Node> waterLevels(4*n);
	vector<ll> heightTree(4*n);
	for(int i = 1; i < n-1; i++) {
		cin >> heights[i];
		totalHeight += heights[i];
		updateMax(1, i, 0, n-1, heights[i], heightTree);
	}
	
	vector<ll> prefixMax(n);
	prefixMax[0] = heights[0];
	for(int i = 1; i < n; i++) {
		prefixMax[i] = max(prefixMax[i-1], heights[i]);
	}
	vector<ll> suffixMax(n);
	suffixMax[n-1] = heights[n-1];
	for(int i = n-2; i >= 0; i--) {
		suffixMax[i] = max(suffixMax[i+1], heights[i]);
	}
	vector<Node> startingWaterLevels(n);
	for(int i = 1; i < n-1; i++) {
		setNode(startingWaterLevels[i], min(prefixMax[i], suffixMax[i]));
	}
	build(1, 0, n-1, waterLevels, startingWaterLevels);
	// for(int i = 0; i < n; i++) {
		// cout << heights[i] << " ";
	// }	
	// cout << endl;
	// for(int i = 0; i < n; i++) {
		// cout << query(1, 0, n-1, i, i, waterLevels) << " ";
	// }
	// cout << endl;
	// cout << query(1, 0, n-1, 0, n-1, waterLevels) << endl;
	// cout << totalHeight << endl;
	
	while(q-->0) {
		int p;
		ll added;
		cin >> p >> added;
		ll newHeight = heights[p]+added;
		ll oldWater = query(1, 0, n-1, p, p, waterLevels);
		
		//process left and right sides separately
		ll leftMax = queryMax(1, 0, n-1, 0, p-1, heightTree);
		ll rightMax = queryMax(1, 0, n-1, p+1, n-1, heightTree);
		
		//if increasing this height doesn't trap more water
		if(leftMax >= newHeight && rightMax >= newHeight) {
			//skip
		}
		//if it does trap more water
		else {
			
			ll leftBound = min(leftMax, newHeight);
			//find first index to left that is >= my new height
			//if it doesn't exist, find first index of largest height
			int leftId = queryNextGreaterLeft(1, 0, n-1, p, leftBound, heightTree);
			//update water level in [leftId+1, p-1] to min(leftMax, newHeight)
			updateSet(1, 0, n-1, leftId+1, p-1, leftBound, waterLevels);
			
			//do the same for right side
			ll rightBound = min(rightMax, newHeight);
			int rightId = queryNextGreaterRight(1, 0, n-1, p, rightBound, heightTree);
			//update water level in [leftId+1, p-1] to min(rightMax, newHeight)
			updateSet(1, 0, n-1, p+1, rightId-1, rightBound, waterLevels);
		}
			
		//new water level at p is equal to max(old water level of p, new height of p)
		updateSet(1, 0, n-1, p, p, max(oldWater, newHeight), waterLevels);
		
		heights[p] = newHeight;
		totalHeight += added;
		updateMax(1, p, 0, n-1, heights[p], heightTree);
		
		cout << query(1, 0, n-1, 0, n-1, waterLevels)-totalHeight << "\n";
	}
	
}