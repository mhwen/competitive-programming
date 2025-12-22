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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	vector<ll> dp(1e6+1);
	dp[0] = 1;
	for(int i = 1; i < sz(dp); i++) {
	    dp[i] = dp[i-1]*(bpow(2, 8*i-4)-(8*i-4)+MOD)%MOD;
	}
	while(t-->0) {
	    int n, m;
	    cin >> n >> m;
	    if(n > m)
	        swap(n, m);
	    ll ans = dp[n];
	    ll over = m-n;
	    ans = ans*bpow(bpow(2, 4*n-2), over)%MOD;
	    cout << ans << "\n";
	}
}