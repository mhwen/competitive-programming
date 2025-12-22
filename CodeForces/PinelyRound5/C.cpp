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
        ll x;
        cin >> n >> x;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        sort(all(a));
        int l = 0, r = n-1;
        vector<ll> order;
        ll ans = 0;
        ll curr = 0;
        while(l <= r) {
            if(curr/x != (curr+a[r])/x) {
                curr += a[r];
                ans += a[r];
                order.pb(a[r]);
                r--;
            }
            else {
                curr += a[l];
                order.pb(a[l]);
                l++;
            }
        }
        cout << ans << "\n";
        for(auto o : order)
            cout << o << " ";
        cout << "\n";
    }
}