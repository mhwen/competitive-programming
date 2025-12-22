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

struct ST {
    int n;
    vector<ll> tree;
    ST(int _n) : n(_n), tree(2*n) {
        for(int i = 0; i < n; i++)
            update(i, 1);
    }
    ll query(int l, int r) {
        l+=n;r+=n;
        ll res = 0;
        while(l<=r) {
            if(l%2==1)
                res += tree[l++];
            if(r%2==0)
                res += tree[r--];
            l/=2;
            r/=2;
        }
        return res;
    }
    void update(int p, ll v) {
        p+=n;
        while(p>0) {
            tree[p]+=v;
            p/=2;
        }
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> con(n);
	vector<pair<int, int>> edges(n-1);
	for(int i = 0; i < n-1; i++) {
	    int a, b;
	    cin >> a >> b;
	    a--; b--;
	    con[a].pb(b);
	    con[b].pb(a);
	    edges[i] = {a, b};
	}
	vector<int> size(n);
	vector<int> tin(n);
	vector<int> dep(n);
	int time = 0;
	function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
	      dep[curr] = d;
	      tin[curr] = time++;
	      size[curr] = 1;
	      for(int next : con[curr]) {
	          if(next == prev)
	              continue;
	            dfs(next, curr, d+1);
	            size[curr] += size[next];
	      }
	};
	dfs(0, -1, 0);
	ll tot = n;
	ST tree(n);
	int q;
	cin >> q;
	while(q-->0) {
	    int type;
	    cin >> type;
	    if(type == 1) {
	        int x, w;
	        cin >> x >> w;
	        x--;
	        tree.update(tin[x], w);
	        tot += w;
	    }
	    else {
	        int edge;
	        cin >> edge;
	        edge--;
	        auto [lo, hi] = edges[edge];
	        if(dep[hi] > dep[lo])
	            swap(lo, hi);
	        cout << abs(tot-2*tree.query(tin[lo], tin[lo]+size[lo]-1)) << "\n";
	    }
	}
}