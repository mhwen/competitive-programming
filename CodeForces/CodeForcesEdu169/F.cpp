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
		vector<ll> pre(n+1);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			pre[i+1] = pre[i]+nums[i];
		}
		map<ll, int> sums;
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = i; j < n; j++) {
				ll sum = pre[j+1]-pre[i];
				sums[sum]++;
				ans += j-i;
			}
		}
		for(auto [_, amt] : sums)
			ans -= amt*(amt-1)/2;

		cout << ans << "\n";
	}
}