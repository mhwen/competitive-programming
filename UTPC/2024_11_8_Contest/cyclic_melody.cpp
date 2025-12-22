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

constexpr ll MOD = 998244353;

ll pow(ll a, ll b) {
	ll p = a;
	ll res = 1;
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
	
	vector<ll> fact(2e5+5);
	vector<ll> invFact(2e5+5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](int a, int b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> cnts(1e6+1);
	int mn = 1e6+1, mx = -1;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		cnts[a]++;
		mn = min(mn, a);
		mx = max(mx, a);
	}
	if(mn == mx && n > 1) {
		cout << 0 << "\n";
		return 0;
	}
	ll ways = n*fact[cnts[mn]-1]%MOD;
	int slots = cnts[mn];
	for(int i = mn+1; i <= mx; i++) {
		if(cnts[i] < slots) {
			ways = 0;
			break;
		}
		if(i == mx && cnts[i] > slots) {
			ways = 0;
			break;
		}
		if(i < mx && slots == 0) {
			ways = 0;
			break;
		}
		ways = ways*fact[cnts[i]]%MOD;
		int over = cnts[i]-slots;
		ways = ways*choose(slots+over-1, slots-1)%MOD;
		slots = over;
	}
	cout << ways << "\n";
}