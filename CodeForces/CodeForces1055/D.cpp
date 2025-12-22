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
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        vector<ll> cost(n);
        vector<ll> single(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            for(ll b = 0; b < 31; b++) {
                if(a[i]&(1LL<<b))
                    cost[i] = b;
            }
            ll bits = __builtin_popcountll(a[i]);
            if(bits > 1)
                cost[i]++;
            if(bits == 2 && a[i]%2==1)
                single[i]++;
        }
        vector<ll> c(n+1), s(n+1);
        for(int i = 0; i < n; i++) {
            c[i+1] = c[i]+cost[i];
            s[i+1] = s[i]+single[i];
        }
        while(q-->0) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            ll ans = c[r+1]-c[l];
            ll ones = s[r+1]-s[l];
            ans -= (ones+1)/2;
            cout << ans << "\n";
        }
    }
}