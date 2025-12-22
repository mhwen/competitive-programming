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

constexpr ll MOD = 1e9+7;

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
	    int n, l, k;
	    cin >> n >> l >> k;
	    vector<ll> dp(n);
	    vector<ll> ans(n);
	    dp[0] = 1;
	    for(int at = 0; at < l; at++) {
	        vector<ll> newDp(n);

	        int rem = l-at;
	        ll p = inv(rem);
	        
	        vector<ll> winners(n+l+5);
	        for(int person = 0; person < n; person++) {
	            ll v = p*dp[person]%MOD;
	            winners[person] += v;
	            winners[person] %= MOD;
	            winners[person+rem] += MOD-v;
	            winners[person+rem] %= MOD;
	        }
	        ll sum = 0;
	        for(int i = 0; i < sz(winners); i++) {
	            sum += winners[i];
	            sum %= MOD;
	            ans[i%n] += sum;
	            ans[i%n] %= MOD;
	            newDp[(i+1)%n] += sum;
	            newDp[(i+1)%n] %= MOD;
	        }
	        dp = newDp;
	    }
	    for(auto a : ans)
	        cout << a << " ";
	    cout << "\n";
	}
}