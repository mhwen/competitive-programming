#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n, k, p;
	cin >> n >> k >> p;
	set<ll> ans;
	for(ll i = 1; i*i <= n; i++) {
		if(n%i == 0) {
			ll a = i;
			ll b = n/i;
			if(a <= k && b <= p)
				ans.insert(a);
			swap(a, b);
			if(a <= k && b <= p)
				ans.insert(a);
		}
	}
	cout << ans.size() << "\n";
	for(ll a : ans)
		cout << a << "\n";
}