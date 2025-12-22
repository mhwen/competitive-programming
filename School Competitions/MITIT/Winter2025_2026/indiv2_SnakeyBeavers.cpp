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
        vector<int> x(n), y(n);
        for(int i = 0; i < n; i++)
            cin >> x[i] >> y[i];
        vector<int> order(n);
        iota(all(order), 0);
        sort(all(order), [&](int a, int b) {
            return x[a] < x[b];
        });
        int ans = 0;
        map<int, int> curr;
        curr[-1e9] = -1e9;
        for(auto i : order) {
            int l = 0, r = x[i];
            int res = 1e9;
            while(l <= r) {
                int m = (l+r)/2;
                int time = x[i]-m;
                auto it = curr.lower_bound(m);
                it--;
                if(it->second <= y[i]+time) {
                    res = m;
                    l = m+1;
                }
                else
                    r = m-1;
            }
            int time = x[i]-res;
            ans = max(ans, time);
            auto it = curr.lower_bound(res);
            it--;
            curr[res] = max(curr[res], max(it->second, y[i]));
        }
        cout << ans << "\n";
    }
}