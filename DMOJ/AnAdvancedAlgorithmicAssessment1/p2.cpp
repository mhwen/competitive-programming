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

constexpr ll INF = 1e12;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<ll> l(n), f(m);
    for(int i = 0; i < n; i++)
        cin >> l[i];
    l.pb(-INF);
    l.pb(INF);
    for(int i = 0; i < m; i++)
        cin >> f[i];
    sort(all(l));
    sort(all(f));
    int fi = 0;
    ll ans = 0;
    for(int i = 0; i < sz(l)-1; i++) {
        ll L = l[i];
        ll R = l[i+1];
        ll prev = L;
        ll large = 0;
        ll tot = R-L;
        while(fi < sz(f) && f[fi] <= R) {
            if(f[fi] >= prev) {
                large = max(large, f[fi]-prev);
                prev = f[fi];
            }
            fi++;
        }
        large = max(large, R-prev);
        ans += tot-large;
    }
    cout << ans << "\n";
}