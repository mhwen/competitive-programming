#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> con(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    vector<int> dep(n);
    vector<vector<int>> par(30, vector<int>(n));
    function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
        dep[curr] = d;
        par[0][curr] = prev;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            dfs(next, curr, d+1);
        }
    };
    dfs(0, 0, 0);
    for(int bit = 1; bit < 30; bit++) {
        for(int i = 0; i < n; i++) {
            par[bit][i] = par[bit-1][par[bit-1][i]];
        }
    }

    auto lca = [&](int a, int b) {
        if(dep[a] < dep[b])
            swap(a, b);
        for(int bit = 29; bit >= 0; bit--) {
            if(dep[a]-dep[b] >= (1<<bit))
                a = par[bit][a];
        }
        if(a == b)
            return a;
        for(int bit = 29; bit >= 0; bit--) {
            if(par[bit][a] != par[bit][b]) {
                a = par[bit][a];
                b = par[bit][b];
            }
        }
        return par[0][a];
    };
    while(q-->0) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int LCA = lca(a, b);
        ll len = dep[a]-dep[LCA]+dep[b]-dep[LCA]+1;
        cout << n+len*(len-1)/2 << "\n";
    }
	return 0;
}
//f