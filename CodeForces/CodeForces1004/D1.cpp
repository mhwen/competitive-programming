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

constexpr ll MOD = 1e9+7;

ll bpow(ll a, ll b) {
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
    return bpow(a, MOD-2);
}

int main() {
    
    vector<ll> fact(10000);
    vector<ll> invFact(10000);
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i%MOD;
        invFact[i] = inv(fact[i]);
    }
    
    auto choose = [&](int a, int b) {
        if(a < b)
            return 0LL;
        return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
    };
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, c, m;
	    cin >> n >> c >> m;
	    vector<int> a(m);
	    for(int i = 0; i < m; i++) 
	        cin >> a[i];
	    
	    vector<ll> dp(m+1);
	    dp[0] = 1;
	    for(int i = 0; i < n; i++) {
	        vector<ll> newDp(m+1);
	        for(int amt = 0; amt <= m; amt++) {
	            for(int take = 0; take <= min(c, amt); take++) {
	                ll res = choose(min(c, amt), take)*dp[amt-take]%MOD;
	                newDp[amt] = (newDp[amt]+res)%MOD;
	            }
	        }
	        for(int amt = 0; amt < c; amt++)
	            newDp[amt] = 0;
	        dp = newDp;
	    }
	    cout << dp[m] << "\n";
	}
}