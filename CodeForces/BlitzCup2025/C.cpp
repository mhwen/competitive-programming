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
	    multiset<ll> a;
	    ll tot = 0;
	    for(int i = 0; i < n; i++) {
	        ll A;
	        cin >> A;
	        a.insert(A);
	        tot += A;
	    }
	    auto dfs = [&](auto&& self, ll curr) -> bool {
	        if(curr < 1)
	            return false;
	        if(a.empty() || *a.begin() > curr)
	            return false;
	        if(a.find(curr) != a.end()) {
	            a.erase(a.find(curr));
	            return true;
	        }
	        return self(self, curr/2) && self(self, (curr+1)/2);
	    };
	    if(dfs(dfs, tot))
	        cout << "YES\n";
	    else
	        cout << "NO\n";
	}
}