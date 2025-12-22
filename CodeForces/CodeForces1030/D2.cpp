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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    ll k;
	    cin >> n >> k;
	    vector<ll> p(n), d(n);
	    for(int i = 0; i < n; i++)
	        cin >> p[i];
	    for(int i = 0; i < n; i++)
	        cin >> d[i];
	    ll q;
	    cin >> q;
	    vector<ll> queries(q);
	    for(int i = 0; i < q; i++)
	        cin >> queries[i];
	    auto left = [](int i) {
	        return 2*i;
	    };
	    auto right = [](int i) {
	        return 2*i+1;
	    };
	    vector<int> con(2*n, -1);
	    map<ll, int> seen;
	    for(int i = 0; i < n; i++) {
	        ll me = (d[i]+p[i])%k;
	        if(seen.count(me))
	            con[left(i)] = right(seen[me]);
	        seen[me] = i;
	    }
	    seen.clear();
	    for(int i = n-1; i >= 0; i--) {
	        ll me = (d[i]+k-p[i]%k)%k;
	        if(seen.count(me))
	            con[right(i)] = left(seen[me]);
	        seen[me] = i;
	    }

	    vector<bool> free(2*n);
	    vector<bool> vis(2*n);
	    function<int(int)> go = [&](int curr) -> int {
	        if(vis[curr])
	            return free[curr];
	        vis[curr] = true;
	        if(con[curr] == -1)
	            return free[curr] = true;
	        return free[curr] = go(con[curr]);
	    };
	    for(int i = 0; i < 2*n; i++) {
	        if(!vis[i])
	            go(i);
	    }
	    
	    seen.clear();
	    vector<int> order(q);
	    iota(all(order), 0);
	    sort(all(order), [&](int a, int b) {
	        return queries[a] > queries[b];
	    });
	    vector<string> ans(q, "YES");
	    int rid = n-1;
	    for(int id : order) {
	        ll pos = queries[id];
	        while(rid >= 0 && p[rid] >= pos) {
	            ll them = (d[rid]+k-p[rid]%k)%k;
	            seen[them] = rid;
	            rid--;
	        }
	        ll me = (k-pos%k)%k;
	        if(seen.count(me) && !free[left(seen[me])])
	            ans[id] = "NO";
	    }
	    for(auto a : ans)
	        cout << a << "\n";
	}
}