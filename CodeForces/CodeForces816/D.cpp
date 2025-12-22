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
	int n, q;
	cin >> n >> q;
	vector<pair<pair<int, int>, int>> s(q);
	for(int i = 0; i < q; i++) {
	    int a, b, x;
	    cin >> a >> b >> x;
	    a--; b--;
	    if(a > b)
	        swap(a, b);
	    s[i] = {{a, b}, x};
	}
	
	auto solve = [&](vector<pair<pair<int, int>, int>>& info) {
	    vector<int> res(n, -1);
	    vector<vector<int>> adj(n);
	    for(auto [i, type] : info) {
	        auto [a, b] = i;
	        if(a == b)
	            res[a] = type;
	        else {
	            if(type == 0)
	                res[a] = res[b] = 0;
	            else
	                adj[a].push_back(b);
	        }
	    }
	    for(int i = 0; i < n; i++) {
	        for(int next : adj[i]) {
	            if(res[next] == 0) {
	                assert(res[i] != 0);
	                res[i] = 1;
	            }
	        }
	        if(res[i] == -1)
	            res[i] = 0;
	        if(res[i] == 0)
	            for(int next : adj[i]) {
	                assert(res[next] != 0);
	                res[next] = 1;
	            }
	    }
	    return res;
	};
	
	vector<int> ans(n);
	for(int bit = 0; bit < 30; bit++) {
	    vector<pair<pair<int, int>, int>> info(q);
	    for(int i = 0; i < q; i++) {
	        info[i] = s[i];
	        info[i].second = (info[i].second & (1<<bit)) ? 1 : 0;
	    }
	    auto res = solve(info);
	    for(int i = 0; i < n; i++)
	        ans[i] |= res[i]<<bit;
	}
	for(auto a : ans)
	    cout << a << " ";
	cout << "\n";
}