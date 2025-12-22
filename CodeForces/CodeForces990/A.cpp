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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a1(n);
		vector<ll> a2(n);
		for(int i = 0; i < n; i++) {
			cin >> a1[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> a2[i];
		}
		ll best = -INF;
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ll a = a1[i];
			ll b = a2[i];
			if(a < b)
				swap(a,b);
			ans += a;
			best = max(best,b);
		}
		cout << ans+best << "\n";
	}
}