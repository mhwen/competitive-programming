#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

void update(int p,int val, vector<int>& tree) {
	int n = sz(tree)/2;
	p += n;
	while(p > 0) {
		tree[p] = max(tree[p], val);
		p >>= 1;
	}
}

int query(int l, int r, vector<int>& tree) {
	int n = sz(tree)/2;
	l += n;
	r += n;
	int best = -1;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			best = max(best, tree[l]);
			l++;
		}
		if(r%2==0) {
			best = max(best, tree[r]);
			r--;
		}
	}
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> vals;
	vector<pair<int, int>> segs(n);
	for(int i = 0; i < n; i++) {
		int a, t;
		cin >> a >> t;
		vals.push_back(a);
		vals.push_back(a+t);
		segs[i] = {a, a+t};
	}
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	for(int i = 0; i < n; i++) {
		segs[i].first = (int)(lower_bound(vals.begin(), vals.end(), segs[i].first)-vals.begin());
		segs[i].second = (int)(lower_bound(vals.begin(), vals.end(), segs[i].second)-vals.begin());
	}
	
	vector<int> tree(2*sz(vals), -1);
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int a, int b) {
		if(segs[a].second == segs[b].second)
			return segs[a].first < segs[b].first;
		return segs[a].second > segs[b].second;
	});
	vector<int> ans(n);
	for(int i : order) {
		int left = segs[i].first;
		int res = query(0, left, tree)+1;
		ans[i] = res;
		update(left, res, tree);
	}
	for(int i : ans)
		cout << i << " ";
	cout << "\n";	
}