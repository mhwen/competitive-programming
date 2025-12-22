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

struct ST {
    int n;
    vector<vector<pair<int, int>>> tree;
    ST(vector<ll>& a) : n(sz(a)), tree(2*n) {
        for(int i = 2*n-1; i > 0; i--) {
            if(i >= n)
                tree[i].pb({a[i-n], i-n});
            else {
                auto& me = tree[i];
                auto& left = tree[i*2];
                auto& right = tree[i*2+1];
                int li = 0, ri = 0;
                while(li < sz(left) && ri < sz(right)) {
                    if(left[li].first <= right[ri].first)
                        me.pb(left[li++]);
                    else
                        me.pb(right[ri++]);
                }
                while(li < sz(left))
                    me.pb(left[li++]);
                while(ri < sz(right))
                    me.pb(right[ri++]);
            }
        }
    }
    vector<int> query(int l, int r, ll target) {
        l+=n; r+=n;
        vector<int> res;
        while(l <= r) {
            if(l%2==1) {
                for(auto [v, id] : tree[l]) {
                    if(v > target)
                        break;
                    res.pb(id);
                }
                l++;
            }
            if(r%2==0) {
                for(auto [v, id] : tree[r]) {
                    if(v > target)
                        break;
                    res.pb(id);
                }
                r--;
            }
            l/=2;
            r/=2;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        ST tree(a);
        
        auto check = [&](ll cap) {
            // cout << "checking " << cap << endl;
            vector<vector<int>> con(n);
            vector<int> d(n);
            vector<int> three;
            for(int i = 0; i < n; i++) {
                auto edges = tree.query(0, i-1, a[i]-cap);
                for(int e : edges) {
                    // cout << i+1 << "-" << e+1 << endl;
                    con[i].pb(e);
                    con[e].pb(i);
                    d[i]++;
                    d[e]++;
                    if(d[i] == 3)
                        three.pb(i);
                    if(d[e] == 3)
                        three.pb(e);
                    if(sz(three) > 1) {
                        // cout << "found 3deg" << endl;
                        return false;
                    }
                }
            }
            if(!three.empty()) {
                for(int next : con[three.front()])
                    d[next]--;
                d[three.front()] = 0;
                int twos = (int)count(all(d), 2);
                return twos == 0;
            }
            else {
                int twos = (int)count(all(d), 2);
                for(int i = 0; i < n; i++) {
                    assert(d[i] <= 2);
                    int rem = 0;
                    if(d[i] == 2)
                        rem++;
                    for(int next : con[i])
                        if(d[next] == 2)
                            rem++;
                    if(twos-rem == 0)
                        return true;
                }
                return false;
            }
        };
        
        
        ll l = -1e9, r = 1e9;
        ll ans = 1e9;
        while(l <= r) {
            ll m = (l+r)/2;
            //can we make it <m
            if(check(m)) {
                ans = m-1;
                r = m-1;
            }
            else {
                l = m+1;
            }
        }
        cout << ans << "\n";
    }
}