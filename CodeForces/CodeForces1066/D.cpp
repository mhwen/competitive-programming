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
        ll l, r;
        cin >> n >> l >> r;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        sort(all(a));
        ll v = a[n/2];
        v = max(v, l);
        v = min(v, r);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ans += abs(a[i]-v);
        }
        cout << ans << "\n";
    }
}