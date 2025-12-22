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
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		vector<bool> used(n);
		int id = (int)(min_element(all(nums))-nums.begin());
		ll me = nums[id];
		ll ans = me;
		for(int i = 0; i < n-1; i++) {
			ll best = me;
			int take = -1;
			for(int j = 0; j < n; j++) {
				if(used[j])
					continue;
				ll c = gcd(me, nums[j]);
				if(c < best) {
					best = c;
					take = j;
				}
			}
			if(take == -1) {
				ans += me*(n-1-i);
				break;
			}
			else {
				used[take] = true;
				me = best;
				ans += me;
			}
		}
		cout << ans << "\n";
	}
}