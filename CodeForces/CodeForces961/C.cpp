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
		ll prev = 0;
		ll ans = 0;
		for(int i = 1; i < n; i++) {
			if(nums[i-1] > 1 && nums[i] == 1) {
				ans = -1;
				break;
			}
			if(nums[i-1] == 1) {
				continue;
			}
			int pows = 0;
			ll hold = nums[i];
			while(hold < nums[i-1]) {
				pows++;
				hold = hold*hold;
			}
			hold = nums[i-1];
			while(hold*hold <= nums[i]) {
				pows--;
				hold = hold*hold;
			}
			prev = max(0LL, prev+pows);
			ans += prev;
		}
		cout << ans << "\n";
	}
}