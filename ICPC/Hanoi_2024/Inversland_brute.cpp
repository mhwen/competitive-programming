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

ll solve(ll a, ll b) {
	// assert(a < b);
	cout << a << " " << b << " b ";
	ll g = gcd(a, b);
	a/=g; b/=g;
	// ll cnt = 0;
	// for(int i = 1; i <= a-1; i++) {
		// cnt += b*i/a;
	// }
	// cout << "solved " << a << " " << b << " " << cnt << endl;
	// return cnt;
	cout << a << " " << b;
	return (a-1)*(b-1)/2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> nums(n);
	ll s = 1;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		s *= nums[i];
	}
	for(int i : nums)
		cout << s/i << "/" << s << endl;
	vector<bool> vis(s+500000);
	int cnt = 0;
	vis[0] = true;
	for(int i = 0; i < sz(vis); i++) {
		for(int j : nums)
			if(i+s/j < sz(vis))
				vis[i+s/j] = vis[i+s/j]|vis[i];
		if(!vis[i]) {
			cout << i << " "; cnt++;
		}
	}
	cout << endl << cnt << endl;
	sort(all(nums));
	reverse(all(nums));
	ll g = 0;
	ll ans = 1;
	ll prevSum = 1;
	for(int i = 0; i < n; i++) {
		ll val = s/nums[i];
		ans = solve(g, val)+ans+(g-1)*prevSum;
		prevSum = solve(g, val);
		cout << " " << ans << endl;
		g = gcd(g, val);
	}
	cout << ans << endl;
	cout << "real ans: " << cnt << endl;
}