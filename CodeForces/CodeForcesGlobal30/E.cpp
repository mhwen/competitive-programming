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
        int n, m;
        cin >> n >> m;
        vector<int> d(n);
        vector<pair<pair<int, int>, ll>> edges(m);
        vector<priority_queue<int>> con(n);
        ll ans = 0;
        for(int i = 0; i < m; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            u--; v--;
            d[u]++;
            d[v]++;
            ans += w;
            edges[i] = {{u, v}, w};
            con[u].push(-i);
            if(u != v)
                con[v].push(-i);
        }
        vector<int> p(n);
        iota(all(p), 0);
        vector<int> guys(n);
        function<int(int)> getPar = [&](int a) {
            if(p[a] == a)
                return a;
            return p[a] = getPar(p[a]);
        };
        auto merge = [&](int a, int b) {
            // cout << "merging " << a+1 << " " << b+1 << endl;
            a = getPar(a);
            b = getPar(b);
            if(a == b)
                return 0;
            if(sz(con[a]) < sz(con[b]))
                swap(a, b);
            p[b] = a;
            guys[a] += guys[b];
            while(!con[b].empty()) {
                con[a].push(con[b].top());
                con[b].pop();
            }
            int got = guys[a]/2;
            guys[a]%=2;
            return got;
        };
        for(int i = 0; i < n; i++) {
            if(d[i]%2==1)
                guys[i]++;
        }
        vector<int> order(m);
        iota(all(order), 0);
        sort(all(order), [&edges](int a, int b){
            return edges[a].second < edges[b].second; 
        });
        
        for(int i : order) {
            auto [uv, w] = edges[i];
            auto [u,v] = uv;
            while(!con[getPar(u)].empty() && -con[getPar(u)].top() <= i) {
                int it = -con[getPar(u)].top();
                con[getPar(u)].pop();
                auto [UV, _w] = edges[it];
                auto [U, V] = UV;
                ans += merge(U, V)*w;
            }
        }
        cout << ans << "\n";
    }
}