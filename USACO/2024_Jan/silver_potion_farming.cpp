#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> con(n);
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    int leaves = 0;
    for(int i = 1; i < n; i++) {
        if(sz(con[i]) == 1)
            leaves++;
    }
    vector<int> pots(n);
    for(int i = 0; i < leaves; i++)
        pots[p[i]]++;
        
    int ans = 0;
    function<int(int, int)> dfs = [&](int curr, int prev) {
        int free = 0;
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            free += dfs(next, curr);
        }
        if(sz(con[curr]) == 1)
            free++;
        int take = min(free, pots[curr]);
        ans += take;
        return free-take;
    };
    dfs(0, -1);
    cout << ans << "\n";
    
}