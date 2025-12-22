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

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> dp1(1e6+1);
	vector<ll> dp2(1e6+1);
	dp1[1] = 4;
	dp2[1] = 3;
	for(int i = 2; i < sz(dp1); i++) {
		dp1[i] = 2*dp1[i-1]%MOD+4*dp2[i-1]%MOD;
		dp1[i] %= MOD;
		dp2[i] = dp1[i-1]+3*dp2[i-1]%MOD;
		dp2[i] %= MOD;
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		cout << (dp1[n]+dp2[n])%MOD << "\n";
	}
}