#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

constexpr ll INF = 1e18;

void update(int pos, ll val, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	while(pos > 0) {
		tree[pos] = min(tree[pos], val);
		pos >>= 1;
	}
}

ll query(int l, int r, vector<ll>& tree) {
	ll ans = INF;
	int n = (int)tree.size()/2;
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> m >> n;
	vector<tuple<int, int, int, ll>> intervals(m);
	
	vector<int> seen;
	
	for(int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		seen.push_back(a);
		seen.push_back(b);
		seen.push_back(c);
		intervals[i] = {a, b, c, d};
	}
	seen.push_back(1);
	seen.push_back(n);
	sort(seen.begin(), seen.end());
	seen.erase(unique(seen.begin(), seen.end()), seen.end());

	vector<ll> leftMinCost(m, INF);
	vector<ll> rightMinCost(m, INF);
	vector<ll> leftTree(2*seen.size(), INF);
	vector<ll> rightTree(2*seen.size(), INF);
	update(0, 0, leftTree);
	update((int)seen.size()-1, 0, rightTree);
	for(int i = 0; i < m; i++) {
		get<0>(intervals[i]) = (int)(lower_bound(seen.begin(), seen.end(), get<0>(intervals[i]))-seen.begin());
		get<1>(intervals[i]) = (int)(lower_bound(seen.begin(), seen.end(), get<1>(intervals[i]))-seen.begin());
		get<2>(intervals[i]) = (int)(lower_bound(seen.begin(), seen.end(), get<2>(intervals[i]))-seen.begin());
		int left = get<0>(intervals[i]);
		int right = get<1>(intervals[i]);
		int hole = get<2>(intervals[i]);
		ll cost = get<3>(intervals[i]);
		ll minLeft = query(left, right, leftTree);
		leftMinCost[i] = min(leftMinCost[i], minLeft+cost);
		update(hole, leftMinCost[i], leftTree);
		ll minRight = query(left, right, rightTree);
		rightMinCost[i] = min(rightMinCost[i], minRight+cost);
		update(hole, rightMinCost[i], rightTree);
	}
	ll best = INF;
	for(int i = 0; i < m; i++) {
		best = min(best, leftMinCost[i]+rightMinCost[i]-get<3>(intervals[i]));
	}
	if(best == INF)
		cout << -1 << "\n";
	else
		cout << best << "\n";
}