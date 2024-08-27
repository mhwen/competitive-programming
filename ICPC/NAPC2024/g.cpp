#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> a_vals(n), b_vals(n);
    for (auto &x : a_vals) {
        cin >> x;
    }
    for (auto &x : b_vals) {
        cin >> x;
    }

    sort(all(a_vals), greater<>{});
    sort(all(b_vals), greater<>{});

    vector dp_a(n+1, vector(k+1, vector(k+1, -INF)));
    vector dp_b(n+1, vector(k+1, vector(k+1, INF)));

    rep(i, 0, k+1) {
        rep(j, 0, k+1) {
            dp_a[n][i][j] = 0;
        }
    }

    for (int i = n-1; i >= 0; i--) {
        // compute dp_b first
        for (int a = 0; a <= k; a++) {
            for (int b = 0; b <= k; b++) {
                int a_pos = a + (i - b);
                int b_pos = b + ((i+1) - a);

                if (min(a_pos, b_pos) < 0) continue;
                if (max(a_pos, b_pos) > n) continue;

                //b bans
                if (a_pos < n) {
                    ckmin(dp_b[i][a][b], dp_a[i+1][a][b]);
                }

                //b picks
                if (b_pos < n && b < k) {
                    ckmin(dp_b[i][a][b], dp_a[i+1][a][b+1] - b_vals[b_pos]);
                }
            }
        }

        // now solve for A
        for (int a = 0; a <= k; a++) {
            for (int b = 0; b <= k; b++) {
                int a_pos = a + (i - b);
                int b_pos = b + (i - a);

                if (min(a_pos, b_pos) < 0) continue;
                if (max(a_pos, b_pos) > n) continue;

                //a picks
                if (a_pos < n && a < k) {
                    ckmax(dp_a[i][a][b], dp_b[i][a+1][b] + a_vals[a_pos]);
                }

                //a bans
                if (b_pos < n) {
                    ckmax(dp_a[i][a][b], dp_b[i][a][b]);
                }
            }
        }
    }

    cout << dp_a[0][0][0] << '\n';

    return 0;
}