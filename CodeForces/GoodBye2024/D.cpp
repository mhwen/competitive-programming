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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 998244353;

ll bpow(ll a, ll b) {
	ll res = 1;
	ll p = a;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b/=2;
	}
	return res;
}

ll inv(ll a) {
	return bpow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<ll> a(n);
		vector<ll> b(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		for(int i = 0; i < n; i++)
			cin >> b[i];
		vector A = a;
		vector B = b;
		sort(all(A));
		sort(all(B));
		ll res = 1;
		for(int i = 0; i < sz(A); i++)
			res = res*min(A[i], B[i])%MOD;
		cout << res;
		
		while(q-->0) {
			int o, x;
			cin >> o >> x;
			x--;
			if(o == 1) {
				int id = (int)(upper_bound(all(A), a[x])-A.begin())-1;
				res = res*inv(min(A[id], B[id]))%MOD;
				a[x]++;
				A[id]++;
				res = res*min(A[id], B[id])%MOD;
			}
			else {
				int id = (int)(upper_bound(all(B), b[x])-B.begin())-1;
				res = res*inv(min(A[id], B[id]))%MOD;
				b[x]++;
				B[id]++;
				res = res*min(A[id], B[id])%MOD;
			}
			cout << " " << res;
		}
		cout << "\n";
	}
}