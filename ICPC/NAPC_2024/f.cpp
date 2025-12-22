#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll INF = 2e18;
constexpr ll MOD = 998244353;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    int SQ = 1000;
    vector<ll> dist(n);
    vector<ll> guys(n);
    vector<vector<pair<int, ll>>> sNodes(n);
    vector<multiset<ll>> mySet(n);
    vector<int> degree(n);
    for(int i = 0; i < n; i++) {
        cin >> guys[i];
    }
    vector<vector<pair<int, ll>>> con(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--; b--;
        con[a].push_back({b, w});
        con[b].push_back({a, w});
        degree[a]++;
        degree[b]++;
    }
    for(int i = 0; i < n; i++) {
        for(auto [next, cost] : con[i]) {
            if(degree[next] >= SQ) {
                sNodes[i].push_back({next, cost});
                mySet[next].insert(cost);
            }
        }
    }
    vector<int> queries(q);
    map<int, int> first;
    for(int i = 0; i < q; i++) {
        cin >> queries[i];
        queries[i]--;
    }
    for(int i = 0; i < q; i++) {
        if(first.count(queries[i]) == 0)
            first[queries[i]] = i;
    }
    ll ans = 0;
    for(int time = q-1; time >= 0; time--) {
        int Q = queries[time];
        ll best = INF;
        ll oldDist = dist[Q];
        if(degree[Q] >= SQ) {
            best = *mySet[Q].begin();
        }
        else {
            for(auto [next, cost] : con[Q]) {
                best = min(best, dist[next]+cost);
            }
        }
        dist[Q] = best;
        if(time == first[Q]) {
            ans += dist[Q]%MOD*guys[Q]%MOD;
            ans %= MOD;
        }
        for(auto [next, cost] : sNodes[Q]) {
            mySet[next].erase(mySet[next].find(oldDist+cost));
            mySet[next].insert(dist[Q]+cost);
        }
    }
    // for(ll d : dist)
    //     cout << d << " ";
    // cout << endl;
    cout << ans << "\n";
}