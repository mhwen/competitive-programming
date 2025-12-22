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
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    set<int> p;
	    for(int i = 0; i < n; i++) {
	        int num;
	        cin >> num;
	        p.insert(num);
	    }
	    int maxP = *p.rbegin();
	    vector<vector<int>> mults(maxP+1);
	    for(auto num : p) {
	        for(int v = num; v <= maxP; v+=num)
	            mults[v].push_back(num);
        }
	    vector<pair<int, int>> tot;
	    vector<stack<pair<int, int>>> q(maxP+1);
	    for(int v = 0; v < sz(mults); v++) {
	        for(auto from : mults[v]) {
	            tot.push_back({v, from});
	            if(from == v)
	                q[0].push({sz(tot)-1, v});
	        }
	    }
	    
	    vector<int> par(maxP+1);

	    iota(all(par), 0);
	    function<int(int)> getPar = [&](int a) {
	        if(a == par[a])
	            return a;
	        return par[a] = getPar(par[a]);
	    };
	    
	    vector<int> size(maxP+1, 1);
	    auto merge = [&](int a, int b) {
	        a = getPar(a);
	        b = getPar(b);
	        if(a == b)
	            return false;
	        if(size[a] < size[b])
	            swap(a, b);
	        par[b] = a;
	        size[a] += size[b];
	        return true;
	    };
	    
	    ll ans = 0;
	    
	    for(int d = 0; d < sz(q); d++) {
	        while(!q[d].empty()) {
	            auto [id, from] = q[d].top();
	            q[d].pop();
	            auto [val, to] = tot[id];
	            if(merge(from, to))
	                ans += d;
	            if(id > 0 && (val == from || tot[id].first != tot[id].second)) {
	                id--;
	                int nextD = from-tot[id].first;
	                if(nextD < sz(q))
	                    q[nextD].push({id, from});
	            }
	        }
	    }
	    cout << ans << "\n";
	}
}