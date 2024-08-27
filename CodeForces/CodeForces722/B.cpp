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
constexpr int INF = 1e9;
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> primes(n+1, INF);
	primes[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(primes[i] == INF) {
			for(int j = i; j <= n; j+=i)
				primes[j] = min(primes[j], i);
		}
	}
	vector<ll> preSum(n+1);
	vector<ll> ans(n+1);
	for(int i = 1; i <= n; i++) {
		ans[i] = preSum[i-1];
		ll factors = 1;
		ll hold = i;
		while(hold > 1) {
			ll count = 1;
			ll f = primes[hold];
			while(hold%f==0) {
				hold /= f;
				count++;
			}
			factors = factors*count%MOD;
		}
		ans[i] += factors;
		ans[i] %= MOD;
		preSum[i] = (preSum[i-1]+ans[i])%MOD;
	}
	cout << ans[n] << "\n";
}