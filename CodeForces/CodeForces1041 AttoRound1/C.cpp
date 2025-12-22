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
        int n, k;
        cin >> n >> k;
        ll res = 0;
        vector<ll> a(n), b(n);
        vector<pair<ll, ll>> segs(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            res += abs(b[i]-a[i]);
            auto [A, B] = minmax(a[i], b[i]);
            segs[i] = {A, B};
        }
        sort(all(segs));
        ll best = 1e10;
        ll prev = -1e10;
        for(auto [A, B] : segs) {
            best = min(best, max(0LL, 2*(A-prev)));
            prev = B;
        }
        cout << res+best << "\n";
    }
}