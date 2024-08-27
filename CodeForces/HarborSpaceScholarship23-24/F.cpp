#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int query_max(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n;
	r += n;
	int ans = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			ans = max(ans, tree[l]);
			l++;
		}
		if(r%2==0) {
			ans = max(ans, tree[r]);
			r--;
		}
	}
	return ans;
}
int query_sum(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n;
	r += n;
	int ans = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			ans += tree[l];
			l++;
		}
		if(r%2==0) {
			ans += tree[r];
			r--;
		}
	}
	return ans;
}

void update_max(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	tree[pos] = val;
	pos >>= 1;
	while(pos > 0) {
		tree[pos] = max(tree[pos*2], tree[pos*2+1]);
		pos >>= 1;
	}
}
void update_sum(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	while(pos > 0) {
		tree[pos] += val;
		pos >>= 1;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> nums(n);
	vector<vector<int>> positions(n+1);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		positions[nums[i]].push_back(i);
	}
	vector<int> vals_tree(2*n+4);
	vector<int> count_tree(2*n+4);
	vector<vector<pair<int, int>>> queries(n+1);
	vector<int> ans(q);
	for(int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		queries[r].push_back({l, i});
	}
	vector<int> prefix(n+1);
	for(int i = 1; i <= n; i++) {
		prefix[i] = prefix[i-1]+min(1, (int)positions[i].size());
		for(int j = 0; j < (int)positions[i].size()-1; j++) {
			int l = positions[i][j];
			int r = positions[i][j+1];
			int max_lower = query_max(l, r, vals_tree);
			update_sum(max_lower, 1, count_tree);
		}
		for(auto query : queries[i]) {
			int l = query.first;
			int r = i;
			int id = query.second;
			ans[id] = prefix[r]-prefix[l-1]+query_sum(l, r, count_tree);
		}
		
		for(int pos : positions[i]) {
			update_max(pos, i, vals_tree);
		}
	}
	
	for(int a : ans)
		cout << a << "\n";
	
}