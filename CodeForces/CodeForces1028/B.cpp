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
	    int n, q;
	    cin >> n >> q;
	    vector<int> b(n);
	    for(int i = 0; i < n; i++) {
	        cin >> b[i];
	    }
	    vector<int> a = b;
	    vector<int> x(q), y(q), z(q);
	    for(int i = 0; i < q; i++) {
	        cin >> x[i] >> y[i] >> z[i];
	        x[i]--;
	        y[i]--;
	        z[i]--;
	    }
	    for(int i = q-1; i >= 0; i--) {
	        int child = a[z[i]];
	        a[x[i]] = max(a[x[i]], child);
	        a[y[i]] = max(a[y[i]], child);
	        if(z[i] != x[i] && z[i] != y[i])
	            a[z[i]] = 0;
	    }
	    auto simulate = [&]() {
	        vector<int> curr = a;
	        for(int i = 0; i < q; i++) {
	            int v = min(curr[x[i]], curr[y[i]]);
	            curr[z[i]] = v;
	        }
	        return curr == b;
	    };
	    if(simulate()) {
	        for(auto v : a)
	            cout << v << " ";
	        cout << "\n";
	    }
	    else
	        cout << -1 << "\n";
	        
	}
}