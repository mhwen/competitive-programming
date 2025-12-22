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
	    ll k;
	    cin >> n >> k;
	    ll ans = 0;
	    priority_queue<ll> q;
	    for(int i = 0; i < n; i++) {
	        ll num;
	        cin >> num;
	        for(ll b = 0; b < 62; b++) {
	            ll B = 1LL << b;
	            if(num&B)
	                ans++;
	            else
	                q.push(-B);
	        }
	    }
	    while(!q.empty() && k+q.top() >= 0) {
	        k += q.top();
	        ans++;
	        q.pop();
	    }
	    cout << ans << "\n";
	}
}