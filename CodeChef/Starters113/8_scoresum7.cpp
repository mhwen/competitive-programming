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

ll pow(ll a, ll b) {
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2)
		res = res*a%MOD;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		ll ans = 0;
		for(int i = 1; i < n; i++) {
			ll val = pow(abs(nums[i]-nums[0]), 7)*pow(2, n-i-1)%MOD;
			ans = (ans+val)%MOD;
		}
		cout << ans << "\n";
	}
}