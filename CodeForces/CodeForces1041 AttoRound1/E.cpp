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
        int n, k;
        cin >> n >> k;
        vector<ll> w(n);
        for(int i = 0; i < n; i++)
            cin >> w[i];
        vector<int> c(n);
        for(int i = 0; i < n; i++)
            cin >> c[i];
        vector<vector<int>> con(n);

        for(int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            con[a].pb(b);
            con[b].pb(a);
        }
        
        vector<vector<int>> free(n);
        vector<set<int>> colors(n);
        
        ll ans = 0;
        function<void(int, int)> dfs = [&](int curr, int prev) {
            set<int> dupes;
            for(int next : con[curr]) {
                if(next == prev)
                    continue;
                dfs(next, curr);
                if(sz(colors[curr]) < sz(colors[next]))
                    swap(colors[curr], colors[next]);
                for(auto C : colors[next]) {
                    if(colors[curr].count(C))
                        dupes.insert(C);
                    colors[curr].insert(C);
                }
                if(sz(free[curr]) < sz(free[next]))
                    swap(free[curr], free[next]);
                for(auto F : free[next])
                    free[curr].pb(F);
            }
            if(c[curr]) {
                dupes.erase(c[curr]);
                if(sz(dupes))
                    ans += w[curr];
                while(!free[curr].empty()) {
                    c[free[curr].back()] = c[curr];
                    free[curr].pop_back();
                }
                colors[curr].insert(c[curr]);
            }
            else {
                free[curr].pb(curr);
                if(sz(dupes) > 1)
                    ans += w[curr];
                if(sz(dupes)) {
                    int C = *dupes.begin();
                    while(!free[curr].empty()) {
                        c[free[curr].back()] = C;
                        free[curr].pop_back();
                    }
                }
                else if(sz(colors[curr])){
                    int C = *colors[curr].begin();
                    while(!free[curr].empty()) {
                        c[free[curr].back()] = C;
                        free[curr].pop_back();
                    }
                }
            }
        };
        dfs(0, -1);
        for(auto F : free[0])
            c[F] = 1;
        cout << ans << "\n";
        for(auto col : c)
            cout << col << " ";
        cout << "\n";
    }
}