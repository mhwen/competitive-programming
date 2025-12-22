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

struct ST {
    int n;
    vector<int> tree;
    ST(int _n) : n(_n), tree(2*n) {}
    int query(int l, int r) {
        l += n;
        r += n;
        int res = 0;
        while(l <= r) {
            if(l%2==1)
                res += tree[l++];
            if(r%2==0)
                res += tree[r--];
            l/=2;
            r/=2;
        }
        return res;
    }
    void update(int p) {
        p += n;
        while(p > 0) {
            tree[p]++;
            p/=2;
        }
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<vector<int>> order(n+1);
	    for(int i = 0; i < n; i++) {
	        int w;
	        cin >> w;
	        order[w].push_back(i);
	    }
	    vector<vector<int>> con(n);
	    for(int i = 0; i < n-1; i++) {
	        int a, b;
	        cin >> a >> b;
	        a--; b--;
	        con[a].push_back(b);
	        con[b].push_back(a);
	    }
	    vector<int> size(n, 1);
	    int id = 0;
	    vector<int> tin(n);
	    function<void(int, int)> dfs = [&](int curr, int prev) {
	        tin[curr] = id++;
	        for(auto next : con[curr])  {
	            if(next == prev)
	                continue;
	            dfs(next, curr);
	            size[curr] += size[next];
	        }
	    };
	    dfs(0, -1);
	    ST st(n);
	    int bad = 0;
	    int ans = 0;
	    for(int w = n; w >= 0; w--) {
	        for(auto node : order[w]) {
	            int l = tin[node];
	            int r = l+size[node]-1;
	            if(st.query(l, r) < bad) {
	                ans = node+1;
	                goto done;
	            }
	        }
	        for(auto node : order[w])
	            st.update(tin[node]);
	        bad += sz(order[w]);
	    }
	    done:
	    cout << ans << "\n";
	}
}