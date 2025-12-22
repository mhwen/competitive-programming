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
	vector<int> a(n);
	for(int i = 0; i < n; i++)
	    cin >> a[i];
	sort(all(a));
	map<vector<int>, int> dp;
	// map<vector<int>, vector<int>> prev;
	function<int()> solve = [&]() {
	    if(dp.count(a))
	        return dp[a];
	    int mex = 0;
	    for(int i : a)
	        if(i == mex)
	            mex++;
	    int best = 0;
	    // vector<int> p;
	    for(int i = 0; i < sz(a); i++) {
	        if(a[i] > 0) {
	            if(i == 0 || a[i] != a[i-1]) {
	                a[i]--;
	                int res = solve();
	                if(res > best) {
	                    best = res;
	                    // p = a;
	                }
	                a[i]++;
	            }
	        }
	    }
	    // prev[a] = p;
	    return dp[a] = mex+best;
	};
	cout << solve()-1 << "\n";
	// while(sz(a)) {
	    // for(auto i : a)
	        // cout << i << " ";
	    // cout << " : " << dp[a]-1 << endl;
	    // a = prev[a];
	// }
}