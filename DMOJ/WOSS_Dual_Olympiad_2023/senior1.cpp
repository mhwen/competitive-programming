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

void update(int p, ll val, vector<ll>& tree) {
	int n = (int)tree.size()/2;
	p += n;
	while(p > 0) {
		tree[p] += val;
		p >>= 1;
	}
}

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<ll> tree(2*n);
	for(int i = 0; i < n; i++) {
		ll s;
		cin >> s;
		update(i, s, tree);
	}
	while(q-->0) {
		int a, b, c;
		cin >> a >> b >> c;
		b--;
		if(a==1) {
			update(b, -c, tree);
			update(b-1, c, tree);
		}
		else if(a==2) {
			update(b, -c, tree);
			update(b+1, c, tree);
		}
		else {
			cout << query(b, c-1, tree) << "\n";
		}
	}
}