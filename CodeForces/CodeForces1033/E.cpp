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
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        ll A = -1;
        auto check = [&](ll lo) {
            ll L = 0, H = 0, loCnt = 0, hiCnt = 0;
            ll hi = lo+k+1;
            ll res = 0;
            for(ll v : a) {
                if(v <= lo) {
                    L += lo-v;
                    loCnt++;
                    res += lo*(lo+1)/2;
                }
                else if(v >= hi) {
                    H += v-hi;
                    hiCnt++;
                    res += hi*(hi+1)/2;
                }
                else
                    res += v*(v+1)/2;
            }
            if(L <= H && H <= L+loCnt) {
                res += (lo+1)*(H-L);
                A = res+H*k;
                return 0;
            }
            else if(H <= L && L <= H+hiCnt) {
                res -= hi*(L-H);
                A = res+L*k;
                return 0;
            }
            if(H < L)
                return -1;
            else
                return 1;
        };
        ll l = 0, r = 1e6+5;
        while(l <= r) {
            ll m = (l+r)/2;
            int res = check(m);
            if(res == 0)
                break;
            else if(res == -1)
                r = m-1;
            else
                l = m+1;
        }
        assert(A != -1);
        cout << A << "\n";
    }
}