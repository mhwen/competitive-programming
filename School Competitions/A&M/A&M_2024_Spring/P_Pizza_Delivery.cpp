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

ll query(int l, int r, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	l+=n; r+=n;
	ll res = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			res += tree[l];
			l++;
		}
		if(r%2==0) {
			res += tree[r];
			r--;
		}
	}
	return res;
}

void update(int p, vector<ll>& tree, ll val) {
	int n = (int)tree.size()/2;
	p += n;
	while(p > 0) {
		tree[p] += val;
		p >>= 1;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	ll k;
	cin >> n >> k;
	vector<vector<int>> points(1e5+1);
	for(int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		points[x].push_back(y);
	}
	for(int i = 1; i <= 1e5; i++)
		sort(points[i].begin(), points[i].end());
	
	function<bool(ll)> check = [&](int dist) {
		vector<ll> tree(2e5+2);
		ll count = 0;
		for(int i = 1; i <= 1e5; i++) {
			if(i-dist-1 >= 1) {
				for(auto y : points[i-dist-1])
					update(y, tree, -1);
			}
			for(auto y : points[i]) {
				count += query(max(1, y-dist), y, tree);
				count += query(y, min((int)1e5, y+dist), tree);
				count -= query(y, y, tree);
				update(y, tree, 1);
			}
		}
		return count >= k;
	};
	
	ll left = 0, right = 1e6;
	while(left <= right) {
		ll mid = (left+right)/2;
		if(check((int)mid))
			right = mid-1;
		else
			left = mid+1;
	}
	cout << left << "\n";

//1 1 1 1 2 2 2 3 3 4
	
}