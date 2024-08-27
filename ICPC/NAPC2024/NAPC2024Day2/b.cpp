#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll MOD = 1e9+7;

// ll myPow(ll a, ll b) {
//     if(b==0)
//         return 1;
//     ll res = pow(a, b/2);
//     res = res*res%MOD;
//     if(b%2==1)
//         res = res*a%MOD;
//     return res;
// }

ll myPow(ll a, ll b) {
    ll res = 1;
    ll cur = a % MOD;
    while (b) {
        if (b & 1) res = (res * cur) % MOD;
        cur = cur * cur % MOD;
        b >>= 1;
    }
    return res;
}


void solve (int n, int m) {
  vector<vector<int>> grid(n, vector<int>(m));
    int trash = 1;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            grid[r][c] = -trash;
            trash++;
        }
    }
    ll ans = 0;

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

    function<void(int, int)> search = [&](int r, int c) {
        c++;
        if(c == m) {
            c = 0;
            r++;
        }
        if(r == n) {
            ans++;
            return;
        }
        int old = grid[r][c];
        for(int num = 1; num <= 3; num++) {
            grid[r][c] = num;
            if(check(r, c))
                search(r, c);
            grid[r][c] = old;
        }
    };
    search(0, -1);
    cerr << ans << "\n";
    // cout << "ans[" << n << "][" << m << "] = " << (myPow(3, n*m)-ans+MOD)%MOD << ";\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for(int n = 1; n <= 7; n++) {
        for(int m = 1; m <= 7; m++) {
            solve(n, m);
        }
    }

    // solve(7, 9);

    vector<vector<ll>> ans(8, vector<ll>(8));ans[1][1] = 0;
    ans[1][2] = 0;
    ans[1][3] = 0;
    ans[1][4] = 0;
    ans[1][5] = 0;
    ans[1][6] = 0;
    ans[1][7] = 0;
    ans[2][1] = 0;
    ans[2][2] = 15;
    ans[2][3] = 339;
    ans[2][4] = 4761;
    ans[2][5] = 52929;
    ans[2][6] = 517761;
    ans[2][7] = 4767849;
    ans[3][1] = 0;
    ans[3][2] = 339;
    ans[3][3] = 16485;
    ans[3][4] = 518265;
    ans[3][5] = 14321907;
    ans[3][6] = 387406809;
    ans[3][7] = 460338013;
    ans[4][1] = 0;
    ans[4][2] = 4761;
    ans[4][3] = 518265;
    ans[4][4] = 43022385;
    ans[4][5] = 486780060;
    ans[4][6] = 429534507;
    ans[4][7] = 792294829;
    ans[5][1] = 0;
    ans[5][2] = 52929;
    ans[5][3] = 14321907;
    ans[5][4] = 486780060;
    ans[5][5] = 288599194;
    ans[5][6] = 130653412;
    ans[5][7] = 748778899;
    ans[6][1] = 0;
    ans[6][2] = 517761;
    ans[6][3] = 387406809;
    ans[6][4] = 429534507;
    ans[6][5] = 130653412;
    ans[6][6] = 246336683;
    ans[6][7] = 579440654;
    ans[7][1] = 0;
    ans[7][2] = 4767849;
    ans[7][3] = 460338013;
    ans[7][4] = 792294829;
    ans[7][5] = 748778899;
    ans[7][6] = 579440654;
    ans[7][7] = 236701429;

    int t;
    cin >> t;
    while(t-->0) {
        ll n, m;
        cin >> n >> m;
        if(n <= 7 && m <= 7)
            cout << ans[n][m] << "\n";
        else if(n == 1 || m == 1)
            cout << 0 << "\n";
        else
            cout << myPow(3, n*m) << "\n";
    }
  
}