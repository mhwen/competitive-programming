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

typedef pair<int, pair<int, int>> P;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<vector<int>> con(n);

	    for(int i = 0; i < n-1; i++) {
	        int a, b;
	        cin >> a >> b;
	        a--; b--;
	        con[a].push_back(b);
	        con[b].push_back(a);
	    }
	    vector<bool> used(n);
	    vector<int> dep(n);
	    vector<int> par(n);
	    vector<set<pair<int, int>>> paths(n);
	    vector<map<int, pair<int, int>>> children(n);
	    set<pair<P, int>> q;
	    
	    auto get = [&](int node) {
	        if(sz(paths[node]) == 1) {
	            return pair{1, pair{node, node}};
	        }
	        auto it = paths[node].rbegin();
	        auto [d1, u] = *it;
	        it++;
	        auto [d2, v] = *it;
	        return pair{d1+d2-1, pair{max(u, v), min(u, v)}};
	    };
	    
	    function<pair<int, int>(int, int, int)> dfs = [&](int curr, int prev, int d) {
	        par[curr] = prev;
	        dep[curr] = d;
	        for(int next : con[curr]) {
	            if(next != prev) {
	                auto info = dfs(next, curr, d+1);
	                info.first++;
	                paths[curr].insert(info);
	                children[curr][next] = info;
	            }
	        }
	        paths[curr].insert({1, curr});
	        q.insert({get(curr), curr});
	        return *paths[curr].rbegin();
	    };
	    dfs(0, -1, 0);

	    vector<int> ans;
	    while(!q.empty()) {
	        auto it = q.rbegin();
	        auto [path, node] = *it;
	        q.erase(*it);
	        if(used[node])
	            continue;
	        auto [u, v] = path.second;
	        ans.push_back(path.first);
	        ans.push_back(u+1);
	        ans.push_back(v+1);
	        while(dep[u] != dep[v]) {
	            if(dep[u] > dep[v]) {
	                used[u] = true;
	                u = par[u];
	            }
	            else {
	                used[v] = true;
	                v = par[v];
	            }
	        }
	        while(u != v) {
	            used[u] = true;
	            u = par[u];
	            used[v] = true;
	            v = par[v];
	        }
	        used[u] = true;
            while(par[u] != -1 && !used[par[u]]) {
                int p = par[u];
                q.erase({get(p), p});
                paths[p].erase(children[p][u]);
                if(!used[u]) {
                    auto myPath = *paths[u].rbegin();
                    myPath.first++;
                    paths[p].insert(myPath);
                    children[p][u] = myPath;
                }
                q.insert({get(p), p});
                u = p;
            }
	    }
	    for(auto a : ans)
	        cout << a << " ";
	    cout << "\n";
	}
}