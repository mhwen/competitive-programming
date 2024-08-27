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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ll pow = nums[i];
			if(pow == 1) {
				ans += n;
				continue;
			}
			for(int j = 0; j < n && pow <= 1000000000; j++) {
				if(pow <= nums[j])
					ans++;
				pow *= nums[i];
			}
		}
		cout << ans << "\n";
	}
}