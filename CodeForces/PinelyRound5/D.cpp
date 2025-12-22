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
        cin >> n;
        vector<int> a(n);
        vector<vector<int>> pos(n+1);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            pos[a[i]].pb(i);
        }
           
        auto get = [&](int i, int v) {
            return (int)(pos[i].end()-lower_bound(all(pos[i]), v));  
        };
        vector<pair<int, int>> s{{0, n}};
        for(int i = 1; i <= n; i++) {
            int prev = 0;
            for(auto [v, p] : s) {
                prev = max(prev, v);
            }
            vector<pair<int, int>> newS;
            newS.pb({prev, n});
            int l = 0;
            int best = 0;
            int currAmt = 0;
            for(int j = sz(pos[i])-1; j >= 0; j--) {
                int p = pos[i][j];
                currAmt++;
                while(l < sz(s) && s[l].second > p) {
                    best = max(best, s[l].first-get(i, s[l].second));
                    l++;
                }
                newS.pb({best+currAmt, p});
            }
            swap(s, newS);
        }
        int ans = 0;
        for(auto [v, _p] : s)
            ans = max(ans, v);
        cout << n-ans << "\n";
    }
}