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
    
    vector<ll> fact(2e5+1);
    vector<ll> invFact(2e5+1);
    fact[0] = 1;
    for(int i = 1; i < sz(fact); i++)
        fact[i] = fact[i-1]*i%MOD;
    invFact.back() = inv(fact.back());
    for(int i = sz(invFact)-2; i >= 0; i--)
        invFact[i] = invFact[i+1]*(i+1)%MOD;
        
    auto choose = [&](int a, int b) {
        return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;  
    };
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int d, t;
	cin >> d >> t;
	ll ans = bpow(2, d)*bpow(d, t)%MOD;
	for(int keep = d-1; keep > 0; keep--) {
	    if((d-keep)%2==1)
	        ans = (ans-bpow(2, keep)*bpow(keep, t)%MOD*choose(d, keep)%MOD+MOD)%MOD;
	    else
	        ans = (ans+bpow(2, keep)*bpow(keep, t)%MOD*choose(d, keep)%MOD+MOD)%MOD;
	}
	cout << ans << "\n";
}