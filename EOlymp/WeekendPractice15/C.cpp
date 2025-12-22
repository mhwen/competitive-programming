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
        cin >> n;
        vector<ll> a(n), b(n);
        map<ll, vector<int>> diffs;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            diffs[b[i]-a[i]].pb(i);
        }
        ll ans = sz(diffs[0]);
        
        auto count = [&](ll l, ll r) {
            auto& z = diffs[0];
            int lo = (int)(lower_bound(all(z), l)-z.begin());
            int hi = (int)(upper_bound(all(z), r)-z.begin()); 
            return hi-lo;
        };
        
        for(auto& [_x, v] : diffs) {
            if(_x == 0)
                continue;
            ll sum = 0;
            ll prev = 0;
            for(auto p : v) {
                ll cost = count(prev, p);
                sum = max(sum+1-cost, 1LL);
                prev = p;
                ans = max(ans, sum+sz(diffs[0]));
            }
        }
        cout << ans << "\n";
    }
    
}