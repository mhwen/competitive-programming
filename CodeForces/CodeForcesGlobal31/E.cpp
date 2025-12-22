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
        ll L, R;
        cin >> L >> R;
        auto check = [&](ll v) {
            ll minMask = 0;
            ll maxMask = 0;
            ll mn = 0;
            ll mx = 0;
            for(ll b = 60; b >= 0; b--) {
                ll bit = (1LL<<b);
                if(v&bit) {
                    if(maxMask+bit-1 < L)
                        maxMask += bit;
                    else
                        mx += bit;
                    if(minMask+bit <= R)
                        minMask += bit;
                    else
                        mn += bit;
                }
                else {
                    if(maxMask+bit <= R) {
                        maxMask += bit;
                        mx += bit;
                    }
                    if(minMask+bit-1 < L) {
                        minMask += bit;
                        mn += bit;
                    }
                }
            }
            if(mn < L || mx > R)
                return false;
            return true;
        };
        ll p1 = 0;
        while(check(p1*2+1)) {
            p1 = p1*2+1;
        }
        ll p2 = 1;
        ll big = L^R;
        while((big-p2+1) > p1 && check(big-p2+1)) {
            p2 *= 2;
        }
        p2/=2;
        cout << p1+p2 << "\n";
    }
}