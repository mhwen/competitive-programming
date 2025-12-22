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
        ll r, x, d;
        int n;
        cin >> r >> x >> d >> n;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            char c;
            cin >> c;
            if(c == '1') {
                ans++;
                r = max(0LL, r-d);
            }
            else {
                if(r < x) {
                    ans++;
                    r = max(0LL, r-d);
                }
            }
        }
        cout << ans << "\n";
    }
}