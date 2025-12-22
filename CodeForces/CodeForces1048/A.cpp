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
        ll k, x;
        cin >> k >> x;
        bool flip = false;
        if(x > (1LL<<k)) {
            x = (1LL<<(k+1))-x;
            flip = true;
        }
        ll bit = -1;
        for(ll b = 0; b < k+1; b++) {
            if(x&(1LL<<b)) {
                bit = b;
                break;
            }
        }
        vector<int> ans;
        for(ll b = bit+1; b < k+1; b++) {
            if(x&(1LL<<b))
                ans.pb(2);
            else
                ans.pb(1);
        }
        cout << sz(ans) << "\n";
        for(auto a : ans) {
            if(flip)
                cout << 3-a << " ";
            else
                cout << a << " ";
        }
        cout << "\n";

    }
}