#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <stack>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

void update(int p, ll val, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	p += n;
	while(p > 0) {
		tree[p] += val;
		tree[p] %= MOD;
		p >>= 1;
	}
}

ll query(int l, int r, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	l += n; r += n;
	ll res = 0;
	while(l <= r) {
		if(l%2==1) {
			res += tree[l];
			res %= MOD;
			l++;
		}
		if(r%2==0) {
			res += tree[r];
			res %= MOD;
			r--;
		}
		l >>= 1;
		r >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		
		vector<ll> keep(2*n);
		vector<ll> rem(2*n);

		stack<pair<int, int>> seen;
		for(int i = 0; i < n; i++) {
			int p;
			cin >> p;
			while(!seen.empty() && seen.top().first > p)
				seen.pop();
			if(!seen.empty()) {
				int id = seen.top().second;

				ll remVal = (query(id, id, keep)+query(id, id, rem))%MOD;
				update(i, remVal, rem);
				
				ll keepVal = (query(id, i-1, keep)+query(id, id, rem))%MOD;;
				update(i, keepVal, keep);
				
			}
			else {
				ll keepVal = query(0, i-1, keep);
				update(i, keepVal+1, keep);
			}
			seen.push({p, i});
		}
		cout << (query(n-1, n-1, keep)+query(n-1, n-1, rem))%MOD << "\n";
	}
}