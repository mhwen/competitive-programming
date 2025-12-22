#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int tot_dp[2][300][300];

void solve() {
    int n;
    cin >> n;
    n++;

    vector<int> a(n);
    rep(i, 1, n) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    vector<int> deg(n);

    rep(i, 0, n-1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        deg[a]++;
        deg[b]++;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> leaves;
    rep(v, 0, n) {
        if (deg[v] == 1) {
            leaves.push_back(v);
        }
    }

    ll ans = 0;

    auto comp_dp = [&](const vector<int> &garbage) {
        int len = sz(garbage);

        auto fills = [&](auto arr) {
            for (in)
        }

        vector<int> psum(len + 1);
        rep(i, 0, len) {
            psum[i+1] = psum[i] + garbage[i];
        }

        vector dp(len, vector<ll>(len, -1));
        rep(i, 0, len) {
            dp[i][i] = a[0];
        }

        rep(i, 1, n) {
            vector nxt(len, vector<ll>(len, -1));
            for (int l = len - 1; l >= 0; l--) {
                rep(r, l, len) {
                    if (dp[l][r] == -1) continue;

                    int slots = psum[r+1] - psum[l];
                    int cur_len = r - l + 1;
                    int garbage_placed = i - cur_len;

                    if (l > 0) {
                        ckmax(nxt[l-1][r], dp[l][r] + a[i]);
                    }

                    if (r < len-1) {
                        ckmax(nxt[l][r+1], dp[l][r] + a[i]);
                    }

                    if (garbage_placed + 1 <= slots) {
                        ckmax(nxt[l][r], dp[l][r]);
                    }
                }
            }

            dp = nxt;
        }

        return dp[0][len-1];
    };

    auto solve = [&](int u, int v) {
        vector<int> par(n, -1);
        auto dfs = [&](auto &&self, int v, int p) -> void {
            for (auto e : adj[v]) {
                if (e != p) {
                    par[e] = v;
                    self(self, e, v);
                }
            }
        };

        dfs(dfs, u, -1);
        vector<bool> garbage(n, true);

        auto mark_non_garbage = [&] {
            int cur = v;
            while (cur != u) {
                garbage[cur] = false;
                cur = par[cur];
            }
            garbage[u] = false;
        };
        mark_non_garbage();

        auto cnt_garbage = [&](auto &&self, int v, int p) -> int {
            int ans = garbage[v] ? 1 : 0;
            for (auto e : adj[v]) {
                if (garbage[e] && e != p) {
                    ans += self(self, e, v);
                }
            }
            return ans;
        };

        vector<int> garbage_cnts;
        auto find_garbage = [&] {
            int cur = v;
            while (cur != u) {
                garbage_cnts.push_back(cnt_garbage(cnt_garbage, cur, -1));
                cur = par[cur];
            }
            garbage_cnts.push_back(cnt_garbage(cnt_garbage, u, -1));
        };
        find_garbage();

        ans = max(ans, comp_dp(garbage_cnts));
    };

    rep(i, 0, sz(leaves)) {
        rep(j, i+1, sz(leaves)) {
            solve(leaves[i], leaves[j]);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}