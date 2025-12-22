#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<ll> dp(k+1);
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        vector<ll> newDp(k+1);
        for(int box = 0; box <= k; box++) {
            int slots = i;
            newDp[box] += dp[box]*slots%MOD;
            newDp[box] %= MOD;
            if(box < k) {
                newDp[box+1] += dp[box];
                newDp[box+1] %= MOD;
            }
        }
        swap(dp, newDp);
    }
    cout << dp[k] << "\n";
}