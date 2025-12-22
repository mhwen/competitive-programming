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
	    int n, m, k;
	    cin >> n >> m >> k;
	    vector<int> a(n);
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	    }
	    vector<int> b(m);
	    for(int i = 0; i < m; i++) {
	        cin >> b[i];
	    }
	    vector<int> masks(1<<m);
	    vector<int> bitCnt(1<<m);
	    for(int mask = 0; mask < (1<<m); mask++) {
	        int res = (1<<30)-1;
	        for(int bit = 0; bit < m; bit++) {
	            if(mask&(1<<bit)) {
	                res = res&b[bit];
	                bitCnt[mask]++;
	            }
	        }
	        masks[mask] = res;
	    }
	    priority_queue<ll> decs;
	    for(int i = 0; i < n; i++) {
	        vector<int> lowest(m+1, a[i]);
	        for(int mask = 0; mask < (1<<m); mask++) {
	            lowest[bitCnt[mask]] = min(lowest[bitCnt[mask]], a[i]&masks[mask]);
	        }
	        for(int j = 0; j < m; j++) {
	            decs.push(lowest[j]-lowest[j+1]);
	        }
	    }
	    ll tot = accumulate(all(a), 0LL);
	    while(k--> 0) {
	        tot -= decs.top();
	        decs.pop();
	    }
	    cout << tot << "\n";
	}
}