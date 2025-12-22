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
	    ll a, b, k;
	    cin >> a >> b >> k;
	    ll tot = k*(a-1)%MOD+1;
	    ll x = 1;
	    for(ll i = 0; i < a; i++) {
	        x = x*(tot-i+MOD)%MOD*inv(i+1)%MOD;
	    }
	    ll tot2 = x*(b-1)%MOD*k+1;
	    cout << tot%MOD << " " << tot2%MOD << "\n";
	}
}