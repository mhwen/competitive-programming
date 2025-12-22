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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    ll n, m;
	    cin >> n >> m;
	    ll mn = n;
	    ll mx = n*(n+1)/2;
	    if(mn <= m && m <= mx) {
	        vector<ll> ans;
	        ll rem = m;
	        for(ll i = 0; i < n; i++) {
	            ll v = n-i;
	            ll ones = v-1;
	            if(rem-v >= v-1) {
	                ans.pb(v);
	                rem-=v;
	            }
	            else {
	                ll target = rem-ones;
	                ans.pb(target);
	                if(target != 1)
	                    ans.pb(1);
	                for(ll V = v; V >= 2; V--) {
	                    if(V == target)
	                        continue;
	                    ans.pb(V);
	                }
	                break;
	            }
	        }
	        cout << ans.front() << "\n";
	        for(int i = 0; i < sz(ans)-1; i++)
	            cout << ans[i] << " " << ans[i+1] << "\n";
	    }
	    else
	        cout << -1 << "\n";
	}
}