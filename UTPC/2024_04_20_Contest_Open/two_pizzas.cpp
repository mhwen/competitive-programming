#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;

const ll mod = (119 << 23) + 1, root = 62;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	ll inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vl a(n);
	vl b(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		cin >> b[i];
		
	vl aMask(2*n);
	vl bMask(2*n);
	for(int i = 0; i < n; i++) {
		if(a[i] == 0) {
			aMask[i] = 1;
			aMask[i+n] = 1;
		}
		if(b[i] == 0) {
			bMask[i] = 1;
			bMask[i+n] = 1;
		}
	}
	reverse(aMask.begin(), aMask.end());
	reverse(bMask.begin(), bMask.end());
	vl aVals = conv(a, bMask);
	vl bVals = conv(b, aMask);
	reverse(bVals.begin(), bVals.end());
	
	ll best = 0;
	for(int i = 0; i < (int)aVals.size(); i++) {
		best = max(best, aVals[i]+bVals[i]);
	}
	cout << best << "\n";

	
}