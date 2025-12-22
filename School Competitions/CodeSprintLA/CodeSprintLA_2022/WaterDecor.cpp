#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

constexpr int SIZE = 1e6+5;

void dfs(int curr, vector<bool>& vis, vector<vector<int>>& children, vector<int>& leftMost, vector<int>& hasWater) {
	if(vis[curr])
		return;
	vis[curr] = true;
	if((int)children[curr].size() == 0)
		hasWater[leftMost[curr]+1]++;
	else {
		for(int next : children[curr]) {
			if(!vis[next])
				dfs(next, vis, children, leftMost, hasWater);
		}
	}
}

void update(int l, int r, int id, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n;
	r += n;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			tree[l] = id;
			l++;
		}
		if(r%2==0) {
			tree[r] = id;
			r--;
		}
	}
}

int query(int pos, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	int id = -1;
	while(pos > 0) {
		if(tree[pos] > id) {
			id = tree[pos];
		}
		pos >>= 1;
	}
	return id;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, pair<int, int>>> circles(n);
	for(int i = 0; i < n; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		circles[i] = {y, {x-r, x+r}};
	}
	sort(circles.begin(), circles.end());
	vector<int> tree(2*SIZE+4, -1);
	vector<int> hasWater(SIZE+5);
	vector<int> degree(3*n);
	vector<vector<int>> con(3*n);
	vector<int> leftMost(3*n, SIZE*10);
	vector<int> rightMost(3*n, -1);
	vector<vector<int>> children(3*n);
	for(int i = 0; i < n; i++) {
		int l = circles[i].second.first;
		int r = circles[i].second.second;
		int mid = (l+r)/2;
		int lId = i*3;
		int rId = i*3+1;
		int mId = i*3+2;
		
		int lNext = query(l, tree);
		if(lNext == -1) {
			//update leftmost and rightmost property of lLine
			leftMost[lId] = rightMost[lId] = l;
		}
		else {
			//draw edge from l to lNext
			degree[lId]++;
			con[lNext].push_back(lId);
			children[lId].push_back(lNext);
		}
		
		int rNext = query(r, tree);
		if(rNext == -1) {
			//update leftmost and rightmost property of rLine
			leftMost[rId] = rightMost[rId] = r;
		}
		else {
			//draw edge from r to rNext
			degree[rId]++;
			con[rNext].push_back(rId);
			children[rId].push_back(rNext);
		}
		
		update(l, mid, lId, tree);
		update(mid, r, rId, tree);
		update(mid, mid, mId, tree);
		//draw edge from mid to l and r
		degree[mId]+=2;
		con[lId].push_back(mId);
		con[rId].push_back(mId);
		children[mId].push_back(lId);
		children[mId].push_back(rId);
	}
	
	//toposort process, updating leftmost and rightmost properties
	queue<int> qq;
	for(int i = 0; i < 3*n; i++) {
		if(degree[i] == 0)
			qq.push(i);
	}
	while(qq.size()) {
		int curr = qq.front();
		qq.pop();
		for(int next : con[curr]) {
			leftMost[next] = min(leftMost[next], leftMost[curr]);
			rightMost[next] = max(rightMost[next], rightMost[curr]);
			degree[next]--;
			if(degree[next] == 0)
				qq.push(next);
		}
	}
	
	//find out which indices get water
	vector<bool> vis(3*n);
	for(int i = 0; i <= 1e6; i++) {
		int id = query(i, tree);
		if(id == -1)
			hasWater[i+1]++;
		else
			dfs(id, vis, children, leftMost, hasWater);
	}
	
	//preprocess hasWater
	for(int i = 1; i < (int)hasWater.size(); i++) {
		hasWater[i] += hasWater[i-1];
	}
	
	for(int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		int lId = query(l, tree);
		int rId = query(r, tree);
		int lBound, rBound;
		if(lId == -1)
			lBound = l;
		else
			lBound = leftMost[lId];
		if(rId == -1)
			rBound = r;
		else
			rBound = rightMost[rId];
		cout << hasWater[rBound+1]-hasWater[lBound] << "\n";
	}
}