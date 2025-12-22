#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
    if(b==0)
        return 1;
    ll res = pow(a, b/2);
    res = res*res%MOD;
    if(b%2==1)
        res = res*a%MOD;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    int trash = 1;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            grid[r][c] = -trash;
            trash++;
        }
    }
    ans = 0;

    auto check = [&](int r, int c) {
        for(int R = 0; R < n; R++) {
            if(r == R)
                continue;
            for(int C = 0; C < m; C++) {
                if(c == C) 
                    continue;
                if(grid[R][C] == grid[R][c] && grid[r][C] == grid[r][c])
                    return false;
                if(grid[R][C] == grid[r][C] && grid[R][c] == grid[r][c])
                    return false;
            }
        }
        return true;
    };

    function<void(int)> search = [&](int r, int c) {
        if(r == n) {
            ans++;
            return;
        }

        c++;
        if(c == m) {
            c = 0;
            r++;
        }
        int old = grid[r][c];
        for(int num = 1; num <= 3; num++) {
            grid[r][c] = num;
            if(check(r, c))
                search(r, c);
            grid[r][c] = old;
        }
    };
    search(0, 0);
    cout << pow(3, n*m) << " " << ans << " " << pow(3, n*m)-ans << "\n";
}