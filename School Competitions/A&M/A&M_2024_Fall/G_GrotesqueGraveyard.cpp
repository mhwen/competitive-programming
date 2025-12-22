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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> diffs(n-1);
	for(int i = 0; i < n; i++) {
		diffs[i] = a[i+1]-a[i];
	}
	ll ans = 0;
	vector<ll> tree(2*n);
	auto update = [&](int l, int r, ll val) {
		l += n; r += n;
		while(l <= r) {
			if(l%2==1)
				tree[l++]+=val;
			if(r%2==0)
				tree[r--]+=val;
			l/=2; r/=2;
		}
	};
	auto query = [&](int p) {
		p += n;
		ll res = 0;
		while(p > 0) {
			res += tree[p];
			p/=2;
		}
		return res;
	};
	bool good = true;
	for(int i = 0; i < sz(diffs); i++) {
		if(diffs[i] > 0) {
			ll take = diffs[i];
			diffs[i] = 0;
			if(i+k < sz(diffs))
				diffs[i+k]+=take;
			update(i+1, min(n-1, i+k), take);
			ans += take;
		}
	}
	for(int i = sz(diffs)-1; i >= 0; i--) {
		if(diffs[i] < 0) {
			ll take = -diffs[i];
			diffs[i] = 0;
			if(i-k >= 0)
				diffs[i-k]-=take;
			update(max(0, i-k+1), i, take);
			ans += take;
		}
	}
	vector<ll> A(n);
	for(int i = 0; i < n; i++) {
		A[i] = query(i);
		if(A[i] > a[i])
			good = false;
	}
	if(!good)
		cout << -1 << "\n";
	else {
		ll diff = a[0]-A[0];
		ll res = ans+diff*((n+k-1)/k);
		cout << res << "\n";
	}

}