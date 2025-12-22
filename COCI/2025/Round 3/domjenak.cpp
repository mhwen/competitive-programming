#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    n*=2;
    vector<vector<int>> con(n);
    vector<int> deg(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    vector<int> color(n, -1);
    function<void(int, int)> colorDfs = [&](int curr, int c) {
        color[curr] = c;
        for(int next : con[curr]) {
            if(color[next] != -1) {
                assert(color[next] == (c^1));
                continue;
            }
            colorDfs(next, c^1);
        }
    };
    
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(color[i] == -1)
            colorDfs(i, 0);
        if(deg[i] == 1)
            q.push(i);
    }
    
    vector<int> paired(n, -1);
    vector<bool> vis(n);
    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        if(vis[curr])
            continue;
        vis[curr] = true;
        for(int next : con[curr]) {
            if(vis[next])
                continue;
            assert(paired[curr] == -1);
            paired[curr] = next;
            vis[next] = true;
        }
        paired[paired[curr]] = curr;
        for(int next : con[paired[curr]]) {
            if(vis[next])
                continue;
            deg[next]--;
            if(deg[next] == 1)
                q.push(next);
        }
    }
    
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++) {
        assert(paired[i] != -1);
        if(color[i] == 0) {
            for(int next : con[i]) {
                if(next == paired[i])
                    continue;
                adj[i].push_back(next);
            }
        }
        else {
            adj[i].push_back(paired[i]);
        }
    }
    
    vector<int> len(n);
    fill(all(vis), false);
    function<int(int)> dfs = [&](int curr) {
        if(vis[curr])
            return len[curr];
        vis[curr] = true;
        int mx = 0;
        for(int next : adj[curr])
            mx = max(mx, dfs(next));
        return len[curr] = mx+1;
    };
    
    for(int i = 0; i < n; i++)
        dfs(i);
        
    int node = (int)(max_element(all(len))-len.begin());
    cout << len[node] << "\n";
    while(len[node] > 1) {
        cout << node+1 << " ";
        for(int next : adj[node]) {
            if(len[next] == len[node]-1) {
                node = next;
                break;
            }
        }
    }
    cout << node+1 << "\n";
}