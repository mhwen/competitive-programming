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
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll big = (1LL<<40)-1;
        auto go = [&](ll b) {
            vector<ll> nums = a;
            ll overMask = big^((1LL<<(b))-1);
            ll has = 0;
            for(auto v : nums) {
                has |= (overMask&v);
            }
            ll ans = __builtin_popcountll(has)+b;
            ll moves = 0;
            for(ll bit = b; bit > 0; bit--) {
                pair<ll, int> found = {0, -1};
                ll mask = (1LL<<bit)-1;
                for(int i = 0; i < n; i++) {
                    found = max(found, {nums[i]&mask, i});
                }
                ll dist = (1LL<<(bit-1))-found.first;
                assert(found.second != -1);
                if(dist > 0) {
                    moves += dist;
                    nums[found.second] += dist;
                }
            }
            return pair{moves, ans};
        };
        vector<pair<ll, ll>> res(33);
        for(ll b = 0; b < sz(res); b++) {
            res[b] = go(b);
            // cout << b << ": " << res[b].first << " " << res[b].second << endl;
        }
        while(q-->0) {
            ll B;
            cin >> B;
            ll ans = 0;
            for(ll b = 0; b < sz(res); b++) {
                if(res[b].first <= B)
                    ans = max(ans, res[b].second);
            }
            cout << ans << "\n";
        }
    }
}