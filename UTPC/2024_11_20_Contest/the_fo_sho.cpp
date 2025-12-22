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


ll pow(ll a, ll b) {
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
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;
	vector<ll> f(n+5);
	vector<ll> invF(n+5);
	f[0] = invF[0] = 1;
	for(int i = 1; i < sz(f); i++) {
		f[i] = f[i-1]*i%MOD;
		invF[i] = inv(f[i]);
	}
	
	vector<int> p(n);
	vector<int> s(n, 1);
	iota(all(p), 0);
	int comps = n;
	ll inner = 1;
	function<int(int)> par = [&](int a) {
		if(a == p[a])
			return a;
		return p[a] = par(p[a]);
	};
	auto merge = [&](int a, int b) {
		a = par(a);
		b = par(b);
		if(a == b)
			return;
		if(s[a] < s[b])
			swap(a, b);
		comps--;
		inner = inner*invF[s[a]]%MOD;
		inner = inner*invF[s[b]]%MOD;
		p[b] = a;
		s[a] += s[b];
		inner = inner*f[s[a]]%MOD;
	};
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		merge(a, b);
		cout << comps << " " << f[comps]*inner%MOD << "\n";
	}
}