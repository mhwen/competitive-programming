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
        b /= 2;
    }
    return res;
}

ll inv(ll a) {
    return bpow(a, MOD-2);
}

bool notZero(ll a, ll p) {
    return a/(p/10)%10 > 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	map<ll, ll> nums;
	for(int i = 0; i < n; i++) {
	    ll num;
	    cin >> num;
	    ll p = 1;
	    while(p < num)
	        p *= 10;
	    nums[num] = p;
	}
	ll tot = (ll)n*(n-1)%MOD*(n-2)%MOD*(n-3)%MOD;
	
	map<ll, ll> mask;
	for(auto [num, _p] : nums) {
	    ll hold = num;
	    ll pow = 1;
	    while(hold/10 > 0) {
	        hold /= 10;
	        pow *= 10;
	        ll rem = num%pow;
	        if(notZero(num, pow) && nums.count(rem))
	            mask[hold]++;
	    }
	}
	
	ll same = 0;
	for(auto [a, aP] : nums) {
	    ll b = a;
	    ll pow = 1;
	    while(b/10 > 0) {
	        b /= 10;
	        pow *= 10;
	        if(nums.count(b)) {
	            ll rem = a%pow;
	            if(!notZero(rem, pow))
	                continue;
	            ll amt = mask[rem];
	            ll bP = aP/pow;
	            
	            //aa
	            //b_
	            if(nums.count(rem*aP+a))
	                amt--;

	            //ab
	            //b_
	            if(nums.count(rem*bP+b))
	                amt--;
	            //a_
	            //ba
	            if(rem == a/bP && notZero(a, bP) && nums.count(a%bP))
	                amt--; 
	            
	            //a_
	            //bb
	            if(bP*bP > aP && rem == b/(bP/pow) && notZero(b, bP/pow) && nums.count(b%(bP/pow)))
	                amt--;    
	            
	            //ab
	            //ba
	            if(a*bP+b == b*aP+a)
	                amt++;
	            // cout << a << " " << b << " " << amt << endl;
	            same += 2*amt;
	            same %= MOD;
	        }
	    }
	}

	ll ans = tot-same+MOD;
	ans %= MOD;
	cout << ans*inv(2)%MOD << "\n";
}