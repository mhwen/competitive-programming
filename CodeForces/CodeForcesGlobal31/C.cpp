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
        ll n;
        int k;
        cin >> n >> k;
        if(k%2==1) {
            for(int i = 0; i < k; i++)
                cout << n << " ";
        }
        else {
            vector<ll> ans(k, n);
            ll B = -1;
            for(ll b = 40; b >= 0; b--) {
                if(n&(1LL<<b)) {
                    B = b;
                    break;
                }
            }
            int id = 0;
            for(ll b = B; b >= 0; b--) {
                ll bit = 1LL<<b;
                if(n&bit) {
                    ans[id%k] ^= bit;
                    id++;
                }
                else {
                    for(int i = 0; i+1 < min(id, sz(ans)); i+=2) {
                        ans[i] |= bit;
                        ans[i+1] |= bit;
                    }
                }
            }
            for(ll a : ans)
                cout << a << " ";
        }
        cout << "\n";
    }
}