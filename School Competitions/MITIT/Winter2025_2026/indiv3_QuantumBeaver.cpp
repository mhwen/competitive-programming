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

constexpr ll MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, k, q;
        cin >> n >> k >> q;
        int SZ = 80*q;
        vector<ll> v(SZ);
        vector<int> cnt(SZ);
        vector<int> left(SZ, -1), right(SZ, -1), par(SZ);
        int ID = 1;
        auto get = [&](vector<int>& child, int i) {
            if(child[i] == -1) {
                child[i] = ID++;
                par[child[i]] = i;
            }
            return child[i];
        };
        auto upd = [&](int i) {
            int L = left[i];
            int R = right[i];
            v[i] = 0;
            cnt[i] = 0;
            int childs = 0;
            if(L != -1) {
                cnt[i] += cnt[L];
                if(cnt[L])
                    childs++;
                v[i] += v[L];
            }
            if(R != -1) {
                cnt[i] += cnt[R];
                if(cnt[R])
                    childs++;
                v[i] += v[R];
            }
            v[i] %= MOD;
            if(childs == 1 && i != 0)
                v[i] = v[i]*2%MOD;
        };
        
        auto go = [&](ll num, ll C, int op) {
            int curr = 0;
            for(ll i = k; i >= 0; i--) {
                ll B = (1LL)<<i;
                if(num&B)
                    curr = get(left, curr);
                else
                    curr = get(right, curr);
            }
            v[curr] += C*op;
            cnt[curr] += op;
            while(curr != 0) {
                upd(par[curr]);
                curr = par[curr];
            }
        };
        
        vector<ll> d(q), c(q);
        vector<int> x(q), y(q);
        vector<vector<int>> enter(n), exit(n);
        for(int i = 0; i < q; i++) {
            cin >> d[i] >> x[i] >> y[i] >> c[i];
            x[i]--; y[i]--;
            enter[x[i]].pb(i);
            exit[y[i]].pb(i);
        }
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            for(int id : enter[i])
                go(d[id], c[id], 1);
            ans += v[0];
            ans %= MOD;
            for(int id : exit[i])
                go(d[id], c[id], -1);
        }
        cout << ans << "\n";
    }
}