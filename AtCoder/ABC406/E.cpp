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

ll brute(ll n, int k) {
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        if(__builtin_popcount(i) == k)
            sum = (sum+i)%MOD;
    }
    return sum;
}

ll bpow(ll a, ll b) {
    ll res = 1;
    ll p = a;
    while(b>0) {
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
    vector<ll> fact(100);
    vector<ll> invFact(100);
    fact[0] = invFact[0] = 1;
    for(int i = 1; i < sz(fact); i++) {
        fact[i] = fact[i-1]*i%MOD;
        invFact[i] = inv(fact[i]);
    }
    
    auto choose = [&](int a, int b) {
        if(a < 0 || b < 0 || b > a)
            return 0LL;
        return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
    };
    
    auto get = [&](int bits, int take) {
        if(bits <= 0 || take <= 0 || take > bits)
            return 0LL;
        return ((1LL<<bits)-1)%MOD*choose(bits-1, take-1)%MOD;
    };
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    ll n;
	    int k;
	    cin >> n >> k;
	    n++;
	    int used = 0;
	    ll ans = 0;
	    ll mask = 0;
	    for(int bit = 62; bit >= 0; bit--) {
	        ll b = 1LL<<bit;
	        if(n&b) {
	            ans += mask*choose(bit, k-used)%MOD;
	            ans %= MOD;
	            ans += get(bit, k-used);
	            ans %= MOD;
	            used++;
	            mask += b;
	            mask %= MOD;
	        }
	    }
	    cout << ans << "\n";
	}
}