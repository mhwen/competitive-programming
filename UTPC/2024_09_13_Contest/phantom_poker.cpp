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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;

	
	auto multiply = [&](vector<ll> a, vector<ll> b) {
		if(accumulate(all(a), 0LL) == 0)
			return b;
		vector<ll> res(13);
		for(int i = 0; i < 13; i++) {
			res[i] += (a[i]+b[i])%MOD;
			res[i] %= MOD;
			for(int j = 0; j < 13; j++) {
				res[i*j%13] += a[i]*b[j]%MOD;
				res[i*j%13] %= MOD;
			}
		}
		return res;
	};
	
	auto exp = [&](int id, ll k) {
		vector<ll> p(13);
		p[id] = 1;
		vector<ll> res(13);
		while(k > 0) {
			if(k%2)
				res = multiply(res, p);
			p = multiply(p, p);
			k /= 2;
		}
		return res;
	};
	
	vector<vector<ll>> Tree(13, vector<ll>(2*n));
	auto query = [&](int l, int r, vector<ll>& tree) {
		l+=n; r+=n;
		ll res = 0;
		while(l<=r) {
			if(l%2==1)
				res += tree[l++];
			if(r%2==0)
				res += tree[r--];
			l/=2;
			r/=2;
		}
		return res;
	};
	auto update = [&](int p, int val, vector<ll>& tree) {
		p += n;
		while(p > 0) {
			tree[p] += val;
			p/=2;
		}
	};
	
	vector<int> ty(n);
	
	for(int i = 0; i < n; i++) {
		int d;
		cin >> d;
		ty[i] = d;
		update(i, 1, Tree[d%13]);
	}
	while(q-->0) {
		int t;
		cin >> t;
		if(t==1) {
			int i, x;
			cin >> i >> x;
			i--;
			update(i, -1, Tree[ty[i]%13]);
			ty[i] = x;
			update(i, 1, Tree[ty[i]%13]);
		}
		else {
			int l, r;
			cin >> l >> r;
			l--; r--;
			vector<ll> res(13);
			for(int i = 0; i < 13; i++) {
				ll cnt = query(l, r, Tree[i]);
				if(cnt > 0)
					res = multiply(res, exp(i, cnt));
			}
			cout << res[5] << "\n";
		}
	}
}