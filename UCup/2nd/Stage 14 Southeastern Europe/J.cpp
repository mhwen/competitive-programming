#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> odds;
		vector<ll> evens;
		for(int i = 0; i < 2*n; i++) {
			ll a;
			cin >> a;
			if(i%2==0)
				evens.push_back(a);
			else
				odds.push_back(a);
		}
		sort(odds.begin(), odds.end());
		sort(evens.rbegin(), evens.rend());
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ans += abs(evens[i]-odds[i]);
		}
		cout << ans << "\n";
	}
}