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
        int n, m;
        cin >> n >> m;
        multiset<int> swords;
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            swords.insert(a);
        }
        vector<int> b(m), c(m);
        vector<pair<int, int>> gains;
        vector<int> ls;
        for(int i = 0; i < m; i++) {
            cin >> b[i];
        }
        for(int i = 0; i < m; i++) {
            cin >> c[i];
            if(c[i] > 0)
                gains.pb({b[i], c[i]});
            else
                ls.pb(b[i]);
        }
        sort(all(gains));
        sort(all(ls));
        int ans = 0;
        for(auto [v, newS] : gains) {
            auto it = swords.lower_bound(v);
            if(it != swords.end() && *it >= v) {
                int next = max(*it, newS);
                swords.erase(it);
                swords.insert(next);
                ans++;
            }
        }
        for(int v : ls) {
            auto it = swords.lower_bound(v);
            if(it != swords.end() && *it >= v) {
                swords.erase(it);
                ans++;
            }
        }
        cout << ans << "\n";
    }
}