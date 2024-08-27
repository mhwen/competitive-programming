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

int query(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	int ans = 1e9;
	l += n;
	r += n;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			ans = min(ans, tree[l]);
			l++;
		}
		if(r%2==0) {
			ans = min(ans, tree[r]);
			r--;
		}
	}
	return ans;
}

void update(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	int id = pos+n;
	tree[id] = val;
	id >>= 1;
	while(id > 0) {
		tree[id] = min(tree[id*2], tree[id*2+1]);
		id >>= 1;
	}
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
		vector<int> tree(2*n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			update(i, nums[i], tree);
		}
		vector<bool> good(n);
		vector<int> left(n, -1);
		int zeros = 0;
		for(int i = 0; i < n; i++) {
			left[nums[i]] = i;
			if(nums[i] == 0) {
				zeros++;
				good[i] = true;
				continue;
			}
			if(left[nums[i]-1] != -1 && query(left[nums[i]-1], i, tree) >= nums[i]-1)
				good[i] = true;
		}
		vector<int> right(n, -1);
		
		for(int i = n-1; i >= 0; i--) {
			right[nums[i]] = i;
			if(nums[i] == 0) {
				continue;
			}
			if(right[nums[i]-1] != -1 && query(i, right[nums[i]-1], tree) >= nums[i]-1)
				good[i] = true;
		}
		bool ans = true;
		for(bool b : good) {
			ans = ans&&b;
		}

		if(ans && zeros==1)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}