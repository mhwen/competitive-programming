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

bool isPrime(ll v) {
    for(ll a = 2; a*a <= v; a++)
        if(v%a==0)
            return true;
    return false;
}

ll mult(ll v, int p) {
    ll res = 1;
    for(int i = 0; i < p; i++)
        res = res*v;
    return res;
}

constexpr ll INF = 2e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> divs(1e6+20);
	for(int i = 1; i < sz(divs); i++) {
	    for(int j = i; j < sz(divs); j+=i)
	        divs[j]++;
	}
	ll n;
	cin >> n;

	ll ans = INF;
	ll s = (ll)sqrt(n);
	for(ll v = s-3; v <= s+3; v++) {
	    if(v <= 0)
	        continue;
	    if(v*v==n && !isPrime(v))
	        ans = min(ans, v);
	}
	for(int p = 3; p <= 18; p++) {
	    s = (ll)pow(n, 1.0/p);
    	for(ll v = s-3; v <= s+3; v++) {
    	    if(v <= 0)
    	        continue;
    	    if(mult(v, p)==n && divs[v] == p)
    	        ans = min(ans, v);
    	}
	}
	
	for(ll i = 1; i <= 10; i++) {
	    if(mult(i, divs[i]) == n)
	        ans = min(ans, i);
	}
	if(ans == INF)
	    ans = -1;
	cout << ans << "\n";
}