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
        if(zeros > ones)
            swap(zeros, ones);
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
        auto check = [&](int m) {
            map<int, int> cnts;
            for(int i = 0; i <= m; i++) {
                cnts[depths[i]]++;
            }
            vector<int> c;
            vector<int> v;
            for(auto [weight,amt] : cnts) {
                int p = 1;
                while(p <= amt) {
                    c.pb(weight*p);
                    v.pb(p);
                    amt -= p;
                    p*=2;
                }
                if(amt) {
                    c.pb(weight*amt);
                    v.pb(amt);
                }
            }
            
            vector<int> dp(zeros+1, -1);
            dp[0] = 0;
            int sum = 0;
            int ans = 0;
            for(int i = 0; i < sz(c); i++) {
                vector<int> newDp(zeros+1, -1);
                bool goed = false;
                for(int z = 0; z < sz(dp); z++) {
                    if(dp[z] == -1)
                        continue;
                    int o = sum-z;
                    if(o+c[i] <= ones) {
                        goed = true;
                        newDp[z] = max(newDp[z], dp[z]+v[i]);
                        ans = max(ans, newDp[z]);
                    }
                    if(z+c[i] <= zeros) {
                        goed = true;
                        newDp[z+c[i]] = max(newDp[z+c[i]], dp[z]+v[i]);
                        ans = max(ans, newDp[z+c[i]]);
                    }
                }
                sum += c[i];
                swap(dp, newDp);
                if(!goed)
                    break;
            }
            return ans==m+1;
        };
        int l = 0, r = leafDepth;
        while(l <= r) {
            int m = (l+r)/2;
            if(check(m))
                l = m+1;
            else
                r = m-1;
        }
        cout << l << "\n";
    }
}