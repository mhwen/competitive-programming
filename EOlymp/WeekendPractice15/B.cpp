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

constexpr int SZ = 30;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> a(n+1);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        vector<vector<ll>> next(n, vector<ll>(SZ));
        vector<ll> seen(SZ, n);
        for(int i = n-1; i >= 0; i--) {
            for(int b = 0; b < SZ; b++) {
                next[i][b] = seen[b];
                if(!(a[i]&(1LL<<b)))
                    seen[b] = i;
            }
        }
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ll v = a[i];
            ll r = i;
            while(r < n && v > 0) {
                ll nextR = n;
                for(int b = 0; b < SZ; b++) {
                    if(v&(1LL<<b))
                        nextR = min(nextR, next[i][b]);
                }
                ll lo = r-i+1;
                ll hi = nextR-i;
                if(lo <= v && v <= hi)
                    ans++;
                r = nextR;
                v &= a[r];
            }
        }
        cout << ans << "\n";
    }
}