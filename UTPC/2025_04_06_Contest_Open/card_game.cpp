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
	int n;
	cin >> n;
	vector<int> c(n);
	for(int i = 0; i < n; i++)
	    cin >> c[i];
	    
	ll ans = 0;
	function<vector<pair<int, ll>>(int, int)> solve = [&](int l, int r) -> vector<pair<int, ll>> {
	    if(l == r)
	        return vector<pair<int, ll>>{{c[l], c[l]}};
	    int m = (l+r)/2;
	    auto L = solve(l, m);
	    auto R = solve(m+1, r);
	    int li = 0, ri = 0;
	    vector<pair<int, ll>> res;
	    while(li < sz(L) && ri < sz(R)) {
	        if(L[li].first > R[ri].first) {
	            res.push_back(L[li]);
	            ans += (ll)(sz(R)-ri)*L[li].first+R[ri].second;
	            li++;
	        }
	        else {
	            res.push_back(R[ri]);
	            ri++;
	        }
	    }
	    while(li < sz(L))
	        res.push_back(L[li++]);
	    while(ri < sz(R))
	        res.push_back(R[ri++]);
	    res.back().second = res.back().first;
	    for(int i = sz(res)-2; i >= 0; i--) {
	        res[i].second = res[i+1].second+res[i].first;
	    }
	    return res;
	};
	solve(0, n-1);
	cout << ans << "\n";
}