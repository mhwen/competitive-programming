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

constexpr ll INF = 1e10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> x(n);
        for(int i = 0; i < n; i++)
            cin >> x[i];
        ll lo = 0, hi = INF;
        int ans = n-1;
        for(int i = 1; i < n-1; i++) {
            ll gap = x[i]-x[i-1];
            ll newLo = max(0LL, gap-hi);
            ll newHi = min(gap-lo, x[i+1]-x[i]);
            if(newLo >= x[i+1]-x[i]) {
                ans--;
                lo = 0;
                hi = x[i+1]-x[i];
            }
            else {
                lo = newLo;
                hi = newHi;
            }
        }
        cout << ans << "\n";
    }
}