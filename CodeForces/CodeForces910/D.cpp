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
		vector<ll> a(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		vector<ll> b(n);
		ll ans = 0;
		vector<ll> begin(n);
		vector<ll> end(n);
		for(int i = 0; i < n; i++) {
			cin >> b[i];
			begin[i] = min(a[i], b[i]);
			end[i] = max(a[i], b[i]);
			ans += abs(a[i]-b[i]);
		}
		sort(begin.begin(), begin.end());
		sort(end.begin(), end.end());
		cout << ans+max(0LL, 2*(begin[n-1]-end[0])) << "\n";
	}
}