#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;
constexpr int LEN = 1e6;


int query(int pos, int const&(*op)(int const&, int const&), vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	int best = tree[pos];
	while(pos > 0) {
		best = op(best, tree[pos]);
		pos >>= 1;
	}
	return best;
}

void update(int l, int r, int val, int const&(*op)(int const&, int const&), vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n; r += n;
	for(; l <= r; l>>=1, r>>=1)  {
		if(l%2==1) {
			tree[l] = op(tree[l], val);
			l++;
		}
		if(r%2==0) {
			tree[r] = op(tree[r], val);
			r--;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	map<int, vector<pair<int, int>>> rangesByHeight;
	vector<int> preSum(LEN+5);
	for(int i = 0; i < n; i++) {
		int pos;
		cin >> pos;
		preSum[pos]++;
	}
	for(int i = 0; i < LEN; i++) {
		preSum[i+1] += preSum[i];
	}
	for(int i = 0; i < m; i++) {
		int l, r, h;
		cin >> l >> r >> h;
		rangesByHeight[h].push_back({l, r});
	}
	vector<int> leftTree(2*(LEN+1), 2*LEN);
	vector<int> rightTree(2*(LEN+1), -1);
	for(int i = 1; i <= LEN; i++) {
		update(i, i, i, min, leftTree);
		update(i, i, i, max, rightTree);
	}
	
	for(auto ra : rangesByHeight) {
		vector<pair<int, int>> ranges = ra.second;
		for(auto curr : ranges) {
			int l = curr.first;
			int r = curr.second;
			int leftMost = query(l, min, leftTree);
			int rightMost = query(r, max, rightTree);
			
			update(l, r, leftMost, min, leftTree);
			update(l, r, rightMost, max, rightTree);
		}
	}

	int best = 0;
	for(int i = 1; i <= LEN; i++) {
		int left = query(i, min, leftTree);
		int right = query(i, max, rightTree);
		best = max(best, preSum[right]-preSum[left-1]);
	}
	cout << best << "\n";
	
}