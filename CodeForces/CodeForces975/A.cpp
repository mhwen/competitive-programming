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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k;
		cin >> n >> k;
		vector<ll> a(n);
		for(ll& i : a)
			cin >> i;
		ll sum = accumulate(all(a), 0LL);
		ll m = *max_element(all(a));
		int best = 0;
		for(int i = 1; i <= n; i++) {
			ll extra = (sum+k)%i;
			if(extra > k)
				continue;
			ll amt = sum+k-extra;
			if(amt >= m*i)
				best = i;
		}
		cout << best << "\n";
	}
}