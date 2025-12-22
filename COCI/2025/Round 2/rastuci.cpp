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

constexpr ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, INF));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        int r = i+1;
        ll val = a[i];
        for(int len = n-1; len >= 0; len--) {
            if(dp[i][len] != INF && dp[i][len+1] != INF)
                assert(dp[i][len] >= dp[i][len+1]);
            if(dp[i][len] == INF)
                continue;
            while(val < dp[i][len] && r < n)
                val += a[r++];
            if(val >= dp[i][len])
                dp[r][len+1] = min(dp[r][len+1], val);
            dp[i+1][len] = min(dp[i+1][len], dp[i][len]+a[i]);
        }
    }
    int ans = 0;
    for(int len = 0; len <= n; len++) {
        if(dp[n][len] != INF)
            ans = len;
    }
    cout << ans << "\n";
    int at = n;
    vector<ll> res;
    while(ans > 0) {
        ll amt = 0;
        int counter = at-1;
        while(amt < dp[at][ans]) {
            amt += a[counter--];
        }
        res.pb(amt);
        at = counter+1;
        ans--;
    }
    reverse(all(res));
    for(auto v : res)
        cout << v << " ";
    cout << "\n";
}