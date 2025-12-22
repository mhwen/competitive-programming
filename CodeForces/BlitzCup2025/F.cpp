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
	vector<vector<int>> con(n);
	for(int i = 0; i < m; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    con[a].push_back(b);
	    con[b].push_back(a);
	}

    vector<int> d(n, -1);
    vector<int> comp;
	
	vector<pair<int, int>> centers;
	
	auto dfs = [&](auto&& self, int curr, int prev, int dist) -> void {
	    comp.push_back(curr);
	    d[curr] = dist;
	    for(auto next : con[curr]) {
	        if(next != prev)
	            self(self, next, curr, dist+1);
	    }
	};

	for(int i = 0; i < n; i++) {
	    if(d[i] == -1) {
	        comp.clear();
	        dfs(dfs, i, -1, 0);
	        int far = i;
	        for(auto c : comp) {
	            if(d[c] > d[far])
	                far = c;
	        }
	        comp.clear();
	        dfs(dfs, far, -1, 0);
	        int start = far;
	        for(auto c : comp) {
	            if(d[c] > d[start])
	                start = c;
	        }
	        int maxD = d[start];
	        int curr = start;
	        while(d[curr] != maxD/2) {
	            for(auto next : con[curr]) {
	                if(d[next] < d[curr]) {
	                    curr = next;
	                    break;
	                }
	            }
	        }
	        centers.push_back({maxD, curr});
	    }
	}
	sort(all(centers));
	reverse(all(centers));
	vector<pair<int, int>> ans;
	for(int i = 1; i < sz(centers); i++) {
	    int a = centers[0].second;
	    int b = centers[i].second;
	    ans.push_back({a, b});
	    con[a].push_back(b);
	    con[b].push_back(a);
	}
	dfs(dfs, 0, -1, 0);
	int far = 0;
	for(int i = 0; i < n; i++) {
	    if(d[i] > d[far])
	        far = i;
	}
	dfs(dfs, far, -1, 0);
	int mxD = 0;
	for(int i = 0; i < n; i++)
	    mxD = max(mxD, d[i]);
	cout << mxD << "\n";
	for(auto [a,b] : ans)
	    cout << a+1 << " " << b+1 << "\n";
}