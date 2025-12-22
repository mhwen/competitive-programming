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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    ll k, l;
	    cin >> n >> k >> l;
	    k*=2; l*=2;
	    vector<ll> a(n);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        a[i]*=2;
	    }
	    ll curr = k;
	    ll time = a.front();
	    for(int i = 1; i < n && curr < l; i++) {
	        ll dist = a[i]-curr;
	        if(dist > time) {
	            ll travel = (dist-time)/2;
	            time += travel;
	            curr += travel+k;
	        }
	        else
	            curr = min(curr, a[i]+time)+k;
	    }
	    cout << time+max(0LL, l-curr) << "\n";
	}
}