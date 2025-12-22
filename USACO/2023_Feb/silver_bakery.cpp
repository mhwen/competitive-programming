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
	    int n;
	    ll C, M;
	    cin >> n >> C >> M;
	    vector<ll> a(n), b(n), c(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i] >> b[i] >> c[i];
	        
	    auto check = [&](ll v) {
	        ll usedC = min(C-1, v);
	        ll usedM = min(M-1, v-usedC);
	        ll transferable = min(usedC, M-1-usedM);
	        ll tc = C-usedC;
	        ll tm = M-usedM;
	        ll lo = 0, hi = transferable;
	        for(int i = 0; i < n; i++) {
	            ll cMax = tc*a[i]+tm*b[i];
	            ll mMax = (tc+transferable)*a[i]+(tm-transferable)*b[i];
	            if(cMax > c[i] && mMax > c[i])
	                return false;
	            if(a[i] > b[i]) {
	                ll over = c[i]-cMax;
	                ll loss = a[i]-b[i];
	                hi = min(hi, over/loss);
	            }
	            else if(a[i] < b[i]) {
	                ll need = cMax-c[i];
	                ll gain = b[i]-a[i];
	                lo = max(lo, (need+gain-1)/gain);
	            }
	        }
	        return lo <= hi;
	    };
	    
	    ll l = 0, r = C+M-2;
	    while(l <= r) {
	        ll m = l+(r-l)/2;
	        if(check(m))
	            r = m-1;
	        else
	            l = m+1;
	    }
	    cout << l << "\n";
	}
}