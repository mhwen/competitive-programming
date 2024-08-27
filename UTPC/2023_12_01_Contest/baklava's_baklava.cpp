#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int query(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l+=n, r+=n;
	int res = -1;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			res = max(res, tree[l]);
			l++;
		}
		if(r%2==0) {
			res = max(res, tree[r]);
			r--;
		}
	}
	return res;
}

void update(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	while(pos > 0) {
		tree[pos] = max(tree[pos], val);
		pos >>= 1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> tree(2*n, -1);
	vector<vector<int>> seen(n);
	ll count = 0;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		a--;
		int left = max(query(0, a-1, tree), query(a+1, n-1, tree));
		auto it = lower_bound(seen[a].begin(), seen[a].end(), left);
		count += (int)(seen[a].end()-it);
		seen[a].push_back(i);
		if((int)seen[a].size() > 1) {
			update(a, seen[a][seen[a].size()-2], tree);
		}
	}
	cout << count << "\n";
}