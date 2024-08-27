#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> bitCounts(30);
	vector<ll> twoPows(n+30);
	twoPows[0] = 1;
	for(int i = 1; i < (int)twoPows.size(); i++) {
		twoPows[i] = twoPows[i-1]*2%MOD;
	}
	for(int i = 0; i < n; i++) {
		int p;
		cin >> p;
		for(int bit = 0; bit < 30; bit++) {
			if(p & (1<<bit)) {
				bitCounts[bit]++;
			}
		}
	}
	ll ans = 0;
	for(int bit = 0; bit < 30; bit++) {
		if(bitCounts[bit] > 1) {
			ll choose = bitCounts[bit]*(bitCounts[bit]-1)/2%MOD;
			ans = (ans+twoPows[bit]*twoPows[n-2]%MOD*choose%MOD)%MOD;
		}
	}
	cout << ans << "\n";
}