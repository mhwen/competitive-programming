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

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	cin >> n >> k;
	
	ll ans = 0;
	vector<int> curr(n);
	auto solve = [&](auto&& self, int d) {
	    if(d == k) {
	        ans++;
	        if(ans >= MOD) ans-=MOD;
	        return;
	    }  
	    for(int i = 0; i < n; i++) {
	        if(curr[i] >= 0) {
	            curr[i]++;
	            self(self, d+1);
	            curr[i]--;
	        }
	        if(curr[i] <= 0) {
	            curr[i]--;
	            self(self, d+1);
	            curr[i]++;
	        }
	    }
	};
	solve(solve, 0);
	cout << ans << "\n";
}