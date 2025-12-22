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
		b /= 2;
	}
	return res;
}

ll inv(ll a) {
	return bpow(a, MOD-2);	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> fact(4e5+5);
	vector<ll> invFact(sz(fact));
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	auto choose = [&](int a, int b) -> ll {
		return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
	};
	
	auto ways = [&](int r, int b, int newR, int newB) -> ll {
		int dr = r-newR;
		int db = b-newB;
		if(dr < 0 || db < 0)
			return 0;
		return choose(r, dr)*choose(b, db)%MOD*inv(choose(r+b, dr+db))%MOD;
	};
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, k;
		cin >> n >> m >> k;
		vector<pair<int, int>> s(k);
		for(int i = 0; i < k; i++) {
			int r, b;
			cin >> r >> b;
			s[i] = {n-r, m-b};
		}
		s.emplace_back(0, 0);
		s.emplace_back(n, m);
		k += 2;
		sort(all(s));
		vector<vector<ll>> direct(k, vector<ll>(k));
		vector<vector<ll>> total(k, vector<ll>(k));
		vector<ll> val(k);
		for(int me = 0; me < k; me++) {
			for(int from = me-1; from >= 0; from--) {
				ll prob = ways(n-s[from].first, m-s[from].second, n-s[me].first, m-s[me].second);
				total[from][me] = prob;
				if(prob == 0)
					continue;
				for(int mid = me-1; mid >= 0; mid--) {
					prob -= direct[from][mid]*total[mid][me]%MOD;
					prob = (prob+MOD)%MOD;
				}
				direct[from][me] = prob;
				ll pReach = ways(n, m, n-s[from].first, m-s[from].second);
				ll pathGain = 2*(s[me].first-s[from].first)+s[me].second-s[from].second;
				ll contribution = (val[from]+pReach*pathGain%MOD)%MOD;
				val[me] += direct[from][me]*contribution%MOD;
				val[me] %= MOD;
			}
			val[me] = val[me]*2%MOD;
		}
		cout << val.back()*inv(2)%MOD << "\n";
	}
	
}