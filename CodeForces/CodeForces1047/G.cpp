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
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<int>> con(n), rev(n);
        vector<bool> a(n), b(n);
        vector<int> deg(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            con[u].pb(v);
            rev[v].pb(u);
            deg[u]++;
        }
        
        function<void(int)> upd2;
        
        auto upd1 = [&](int v) {
            if(a[v])
                return;
            a[v] = true;
            for(int prev : rev[v])
                upd2(prev);
        };
        
        upd2 = [&](int v) {
            if(b[v])
                return;
            b[v] = true;
            for(int prev : rev[v]) {
                deg[prev]--;
                if(deg[prev] == 0)
                    upd1(prev);
            }
        };
        
        while(q-->0) {
            int type, v;
            cin >> type >> v;
            v--;
            if(type == 1) {
                upd1(v);
                upd2(v);
            }
            else {
                if(a[v])
                    cout << "NO\n";
                else
                    cout << "YES\n";
            }
        }
    }
}