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
	vector<vector<pair<int, int>>> con(n);
	vector<vector<pair<int, int>>> rev(n);
	set<int> c;
	for(int i = 0; i < m; i++) {
	    int a, b, d;
	    cin >> a >> b >> d;
	    a--; b--;
	    con[a].push_back({b, d});
	    rev[b].push_back({a, d});
	    c.insert(d);
	}
	vector<bool> vis(n);
	vector<bool> vis2(n);
	priority_queue<pair<int, int>> q;
	priority_queue<pair<int, int>> q2;
	q.push({0, 0});
	q2.push({0, 0});
	bool bad = false;
	for(auto cost : c) {
	    while(!q2.empty() && -q2.top().first <= cost) {
	        auto [_, curr] = q2.top();
	        q2.pop();
	        if(vis2[curr])
	            continue;
	        vis2[curr] = true;
	        for(auto [next, d] : rev[curr])
	            q2.push({-d, next});
	    }
	    while(!q.empty() && -q.top().first <= cost) {
	        auto [_, curr] = q.top();
	        q.pop();
	        if(vis[curr])
	            continue;
	        vis[curr] = true;
	        if(!vis2[curr]) {
	            bad = true;
	            goto done;
	        }
	        for(auto [next, d] : con[curr])
	            q.push({-d, next});
	    }
	}
	done:
	if(bad)
	    cout << "NO\n";
	else
	    cout << "YES\n";
}