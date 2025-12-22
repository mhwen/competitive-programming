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

constexpr ll MOD = 1e9+7;

ll bpow(ll a, ll b) {
    ll res = 1;
    ll p = a;
    while(b > 0) {
        if(b%2==1)
            res = res*p%MOD;
        p = p*p%MOD;
        b/=2;
    }
    return res;
}

ll inv(ll a) {
    return bpow(a, MOD-2);
}

typedef vector<vector<ll>> mat;

mat multiply(mat a, mat b) {
    int n = sz(a);
    int m = sz(b[0]);
    int k = sz(a[0]);
    assert(k == sz(b));
    mat res(n, vector<ll>(m));
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            for(int i = 0; i < k; i++) {
                res[r][c] += a[r][i]*b[i][c]%MOD;
                res[r][c] %= MOD;
            }
        }
    }
    return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> con(n);

	for(int i = 0; i < m; i++) {
	    int u, v, t;
	    cin >> u >> v >> t;
	    u--; v--;
	    con[u].push_back({v, t-1});
	    con[v].push_back({u, t-1});
	}
	mat adj(5*n, vector<ll>(5*n));
	mat start(5*n, vector<ll>(1));
	start[0][0] = 1;
	for(int i = 0; i < n; i++) {
	    vector<int> amts(5);
	    for(auto [_, t] : con[i])
	        amts[t]++;
	    for(int j = sz(amts)-2; j >= 0; j--) {
	        amts[j] += amts[j+1];
	        adj[i*5+j+1][i*5+j] = (ll)amts[j+1]*inv(amts[j])%MOD;
	    }
	    for(auto [to, t] : con[i]) {
	        adj[to*5][i*5+t] += inv(amts[t]);
	        adj[to*5][i*5+t] %= MOD;
	    }
	}
	for(int i = 0; i < 5*n; i++)
	    adj[i][5*(n-1)] = 0;
	adj[5*(n-1)][5*(n-1)] = 1;
	
	mat res(5*n, vector<ll>(5*n));
	for(int i = 0; i < 5*n; i++)
	    res[i][i] = 1;
	while(k > 0) {
	    if(k%2==1)
	        res = multiply(adj, res);
	    adj = multiply(adj, adj);
	    k/=2;
	}
	res = multiply(res, start);
	cout << res[5*(n-1)][0] << "\n";
}