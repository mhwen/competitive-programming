#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll INF = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t-->0) {

        int n, m, k;
        cin >> n >> m >> k;
        vector<int> starts(k);
        for(int i = 0; i < k; i++) {
            cin >> starts[i];
            starts[i]--;
        }
        vector<int> d(n);
        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }
        vector<vector<pair<int, ll>>> con(n);
        for(int i = 0; i < m; i++) {
            int a, b;
            ll w;
            cin >> a >> b >> w;
            a--; b--;
            con[a].push_back({b, w});
            con[b].push_back({a, w});
        }
        vector<ll> dists(n, INF);
        vector<int> seen(n);
        priority_queue<pair<ll, int>> q;
        for(int start : starts) {
            q.push({0, start});
            seen[start] = 1e9;
        }
        while(!q.empty()) {
            auto curr = q.top();
            q.pop();
            ll dist = -curr.first;
            int id = curr.second;
            seen[id]++;
            if(seen[id] <= d[id])
                continue;
            if(dists[id] != INF)
                continue;
            dists[id] = dist;
            for(auto next : con[id]) {
                int nextId = next.first;
                ll addDist = next.second;
                q.push({-(dist+addDist), nextId});
            }
        }
        if(dists[0] == INF)
            cout << -1 << "\n";
        else
            cout << dists[0] << "\n";

    }
}