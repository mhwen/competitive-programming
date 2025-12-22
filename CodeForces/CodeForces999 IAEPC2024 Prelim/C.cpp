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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        a[i] = i-a[i];
	    }
	    vector<ll> dp(n);
	    dp[0] = (a[0] == 0) ? 1 : 0;
	    for(int i = 1; i < n; i++) {
	        if(a[i] == a[i-1]+1) {
	            dp[i] += dp[i-1];
	            dp[i] %= MOD;
	        }
	        if(i > 1) {
	            if(a[i] == a[i-2]+1) {
	                dp[i] += dp[i-2];
	                dp[i] %= MOD;
	            }
	        }
	        else {
	            if(a[1] == 0)
	                dp[i] = (dp[i]+1)%MOD;
	        }
	        // cout << dp[i] << "\n";
	    }
	    ll ans = dp.back();
	    if(n > 1)
	        ans = (ans+dp[sz(dp)-2])%MOD;
	    else
	        ans++;
	    cout << ans << "\n";
	}
}