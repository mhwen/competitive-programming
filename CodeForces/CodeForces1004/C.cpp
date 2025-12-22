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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    map<int, ll> dp;
	    dp[0] = 1;
	    int xr = 0;
	    for(int i = 0; i < n; i++) {
	        int a;
	        cin >> a;
	        //b b xr -> b b new
	        
	        //b b xr -> b xr xr

	        //xr xr xr -> xr xr new
	        int need = xr^a;
	        dp[xr] = dp[xr]*3%MOD;
	        dp[xr] = (dp[xr]+2*dp[need])%MOD;
	        xr ^= a;
	    }
	    ll res = 0;
	    for(auto [a, b] : dp) {
	        res = (res+b)%MOD;
	    }
	    cout << res << "\n";
	}
}