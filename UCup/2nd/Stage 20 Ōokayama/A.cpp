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
	vector<ll> sums(n+1);
	sums[0] = 0;
	ll ans = 0;
	for(int i = 1; i < n; i++) {
		sums[i] = (sums[i-1]*2%MOD+1)%MOD;
		ans = (ans+sums[i])%MOD;
	}
	cout << ans << "\n";
}