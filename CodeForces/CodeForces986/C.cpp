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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		ll v;
		cin >> n >> m >> v;
		vector<ll> a(n);
		vector<ll> pSum(n+1);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			pSum[i+1] = pSum[i]+a[i];
		}
		auto solve = [&]() {
			vector<int> p(n+1);
			ll curr = 0;
			for(int i = 0; i < n; i++) {
				p[i+1] += p[i];
				curr += a[i];
				if(curr >= v) {
					curr = 0;
					p[i+1]++;
				}
			}
			return p;
		};
		auto pre = solve();
		reverse(all(a));
		auto suf = solve();
		reverse(all(suf));
		
		ll best = -1;
		int r = 0;
		for(int l = 0; l <= n; l++) {
			while(r < n && pre[l]+suf[r+1]>=m)
				r++;
			if(suf[r]+pre[l]>=m)
				best = max(best, pSum[r]-pSum[l]);
		}
		cout << best << "\n";

	}
}