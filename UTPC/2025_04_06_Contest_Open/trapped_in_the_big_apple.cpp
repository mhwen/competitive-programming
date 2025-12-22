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
    
    ll inv2 = 500000004;
    
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ll N = n%MOD;
	ll N2 = n;
	map<ll, int> f;
	for(ll i = 2; i*i <= N2; i++) {
	    while(n%i==0) {
	        f[i]++;
	        n/=i;
	    }
	}
	if(n > 1)
	    f[n]++;
	ll ans = 0;
	
	vector<pair<ll, ll>> prev{{1, 1}};
	for(auto [p, amt] : f) {
	    vector<pair<ll, ll>> next = prev;
	    ll v = p;
	    for(ll i = 1; i <= amt; i++) {
	        ll phi = (v-v/p)%MOD;
	        for(auto [prevV, prevPhi] : prev) {
	            next.push_back({prevV*v%MOD, prevPhi*phi%MOD});
	        }
	        v *= p;
	    }
	    prev = next;
	}
	for(auto [val, phi] : prev) {
	    if(val == 1)
	        ans = (ans+1)%MOD;
	    else
	        ans = (ans+val*phi%MOD*inv2%MOD)%MOD;
	}
	cout << ans*N%MOD;
}