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

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, m;
	    cin >> n >> m;
	    vector<vector<int>> con(n);
	    for(int i = 0; i < m; i++) {
	        int u, v;
	        cin >> u >> v;
	        u--; v--;
	        con[u].pb(v);
	        con[v].pb(u);
	    }
	    vector<int> dist(n, INF);
        dist[0] = 0;
        int time = 0;
        while(dist[n-1] == INF) {
            vector<int> newDist(n, INF);
            for(int i = 0; i < n; i++) {
                newDist[i] = min(newDist[i], dist[i]+1);
                int mod = time%sz(con[i]);
                int next = con[i][mod];
                newDist[next] = min(newDist[next], dist[i]);
            }
            swap(dist, newDist);
            time++;
        }
        cout << time << " " << dist[n-1] << "\n";
	}
}