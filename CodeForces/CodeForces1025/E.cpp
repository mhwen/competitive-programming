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
#define pb push_back

constexpr ll MOD = 998244353;

ll bpow(ll a, ll b) {
    ll res = 1;
    ll p = a;
    while(b>0) {
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
    vector<ll> fact(1000);
    vector<ll> invFact(1000);
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i%MOD;
        invFact[i] = inv(fact[i]);
    }
    
    auto choose = [&](int a, int b) {
        if(b > a || a < 0 || b < 0)
            return 0LL;
        return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
    };
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, k;
	    cin >> n >> k;
	    string s;
	    cin >> s;
	    vector<ll> dp(k+1);
	    dp[0] = 1;
	    for(int i = n-1; i >= 0; i--) {
	        vector<ll> newDp(k+1);
	        for(int above = 0; above <= k; above++) {
	            for(int me = 0; me+above <= k; me++) {
	                int rem = above-me+1-s[i]+'0';
	                if(rem < 0)
	                    break;
	                int next = me+above;
	                newDp[next] += dp[above]*choose((rem)/2+me, me);
	                newDp[next] %= MOD;
	            }
	        }
	        dp = newDp;
	    }
	    cout << dp[k] << "\n";
	}
}