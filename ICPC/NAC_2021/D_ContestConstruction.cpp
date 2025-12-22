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
	int n, k;
	cin >> n >> k;
	vector<int> d(n+1);
	for(int i = 1; i <= n; i++)
	    cin >> d[i];
	sort(all(d));
	
	vector dp(n+1, vector(n+1, vector<ll>(k+1)));
	for(int i = 1; i <= n; i++)
	    dp[i][0][1] = 1;
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
	    for(int prev = i-1; prev >= 0; prev--) {
	        for(int pp = prev-1; pp >= 0; pp--) {
	            for(int cnt = 0; cnt < k; cnt++) {
	                if(d[i] <= d[prev]+d[pp] || pp == 0) {
	                    dp[i][prev][cnt+1] += dp[prev][pp][cnt];
	                    if(cnt+1 == k)
	                        ans += dp[prev][pp][cnt];
	                }
	            }
	        }
	    }
	}
	cout << ans << "\n";
}