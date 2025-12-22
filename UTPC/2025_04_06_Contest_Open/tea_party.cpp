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

constexpr int root = 330;
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> dp(1e5+1);
	dp[0] = 1;
	for(int i = 1; i <= min(n, root); i++) {
	    int w;
	    cin >> w;
	    for(int j = min(i*i, sz(dp)-1); j >= w; j--)
	        dp[j] = (dp[j]+dp[j-w])%MOD;
	}
	ll ans = accumulate(all(dp), 0LL);
	ans %= MOD;
	for(int i = root; i < n; i++) {
	    ans = ans*2%MOD;
	}
	cout << ans << "\n";
}