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

constexpr ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        ll z;
        cin >> n >> z;
        vector<ll> x(n+2);
        for(int i = 0; i < n; i++)
            cin >> x[i];
        x[n] = INF;
        vector<vector<int>> next(20, vector<int>(n+1));
        next[0][n] = n;
        int R = n;
        for(int i = n-1; i >= 0; i--) {
            while(x[R-1]-x[i] > z)
                R--;
            next[0][i] = R;
            // cout << x[i] << " goes to " << x[next[0][i]] << endl;
        }
        for(int b = 1; b < 20; b++) {
            for(int i = 0; i < sz(next[b]); i++) {
                next[b][i] = next[b-1][next[b-1][i]];
            }
        }
        vector<vector<pair<int, ll>>> merge(20, vector<pair<int, ll>>(n+1));
        merge[0][n] = {n, 0};
        
        auto go = [&](int w, int y) {
            if(w == y) {
                return pair{w, 0LL};
            }
            ll amt = 0;
            for(int b = 19; b >= 0; b--) {
                if(next[b][w] != next[b][y]) {
                    w = next[b][w];
                    y = next[b][y];
                    amt += (1LL<<b)*2;
                }
            }
            assert(next[0][w] == next[0][y]);
            return pair{next[0][w], amt+2};
        };
        
        for(int i = 0; i < n; i++) {
            int w = i;
            int y = i+1;
            auto A = go(w, y);
            auto B = go(y, next[0][w]);
            B.second++;
            merge[0][i] = min(A, B);
            // cout << x[i] << " " << x[i+1] << " merges to " << x[merge[0][i].first] << " " << merge[0][i].second << endl;
        }
        for(int b = 1; b < 20; b++) {
            for(int i = 0; i < sz(merge[b]); i++) {
                auto [pos, amt] = merge[b-1][i];
                auto [npos, namt] = merge[b-1][pos];
                merge[b][i] = {npos, amt+namt};
            }
        }
        int q;
        cin >> q;
        while(q-->0) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            // cout << "answering " << x[l] << " to " << x[r] << endl;
            ll ans = 0;
            int curr = l;
            for(int b = 19; b >= 0; b--) {
                auto [pos, amt] = merge[b][curr];
                if(pos < r) {
                    // cout << "merged to " << pos << endl;
                    ans += amt;
                    curr = pos;
                }
            }
            int w = curr;
            int y = w+1;
            if(w <= r)
                ans++;
            if(y <= r)
                ans++;
            for(int b = 19; b >= 0; b--) {
                if(next[b][w] <= r) {
                    // cout << x[w] << " went to " << x[next[b][w]] << endl;
                    w = next[b][w];
                    ans += (1LL<<b);
                }
                if(next[b][y] <= r) {
                    // cout << x[y] << " went to " << x[next[b][y]] << endl;
                    y = next[b][y];
                    ans += (1LL<<b);
                }
            }
            if(w == y)
                ans--;
            cout << ans << "\n";
        }
        
    }
}