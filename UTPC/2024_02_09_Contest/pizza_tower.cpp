#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;

typedef long long ll;

ll queryTree(int left, int right, vector<ll>& tree) {
	ll ans = 0;
	int n = (int)tree.size()/2;
	left += n;
	right += n;
	for(; left <= right; left>>=1, right>>=1) {
		if(left%2==1) {
			ans += tree[left];
			left++;
		}
		if(right%2==0) {
			ans += tree[right];
			right--;
		}
	}
	return ans;
}

void updateTree(int pos, ll val, vector<ll>& tree) {
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
	int n;
	cin >> n;
	vector<ll> x(n);
	vector<ll> y(n);
	vector<ll> s(n);
	
	vector<ll> tree(2*n);
	
	vector<int> order(n);

	vector<ll> seenY(n);
	
	for(int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> s[i];
		seenY[i] = y[i];
	}
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int a, int b) {
		if(x[a] == x[b])
			return y[a] < y[b];
		return x[a] < x[b];
	});
	sort(seenY.begin(), seenY.end());
	vector<ll> ans(n);
	for(int i : order) {
		int dist = (int)(upper_bound(seenY.begin(), seenY.end(), y[i])-seenY.begin())-1;
		updateTree(dist, s[i], tree);
		ans[i] = queryTree(0, dist, tree);
	}
	for(ll l : ans)
		cout << l << "\n";
}