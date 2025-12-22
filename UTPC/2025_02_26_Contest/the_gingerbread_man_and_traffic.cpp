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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> r(n);
	vector<int> g(n);
	for(int i = 0; i < n; i++)
	    cin >> r[i] >> g[i];
	vector<vector<pair<int, int>>> con(n);
	for(int i = 0; i < m; i++) {
	    int u, v, l;
	    cin >> u >> v >> l;
	    u--; v--;
	    con[u].emplace_back(v, l);
	    con[v].emplace_back(u, l);
	}
	
	auto wait = [&](int i, int time) {
	    int tot = r[i]+g[i];
	    if(time%tot < r[i])
	        return time;
	    else
	        return time+tot-time%tot;
	};
	
	vector<bool> vis(n);
	
	priority_queue<pair<int, int>> q;
	q.push({0, 0});
	while(!q.empty()) {
	    auto [dist, curr] = q.top();
	    q.pop();
	    dist = -dist;
	    if(vis[curr])
	        continue;
	    vis[curr] = true;
	    if(curr == n-1) {
	        cout << dist << "\n";
	        break;
	    }
	    dist = wait(curr, dist);
	    for(auto [next, d] : con[curr]) {
	        if(!vis[next])
	            q.push({-(dist+d), next});
	    }
	}
}