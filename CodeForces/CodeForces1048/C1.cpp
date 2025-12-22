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
        int n, zeros;
        cin >> n >> zeros;
        int ones = n-zeros;
        vector<vector<int>> con(n);
        for(int i = 1; i <= n-1; i++) {
            int p;
            cin >> p;
            p--;
            con[p].pb(i);
        }
        int leafDepth = n;
        vector<int> depths(n);
        function<void(int, int)> dfs = [&](int curr, int d) {
            depths[d]++;
            if(con[curr].empty())
                leafDepth = min(leafDepth, d);
            for(int next : con[curr]) {
                dfs(next, d+1);
            }
        };
        dfs(0, 0);
        vector<bool> dp(n+1);
        dp[0] = true;
        int sum = 0;
        int ans = 0;
        for(int i = 0; i <= leafDepth; i++) {
            vector<bool> newDp(n+1);
            for(int z = 0; z < sz(dp); z++) {
                if(!dp[z])
                    continue;
                int o = sum-z;
                if(o+depths[i] <= ones)
                    newDp[z] = true;
                if(z+depths[i] <= zeros)
                    newDp[z+depths[i]] = true;
            }
            sum += depths[i];
            swap(dp, newDp);
            if(accumulate(all(dp), 0) == 0) {
                break;
            }
            ans++;
        }
        cout << ans << "\n";
    }
}