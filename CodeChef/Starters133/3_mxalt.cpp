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
		sort(nums.begin(), nums.end());
		int start = 0, end = n-1;
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			if(i%2==0)
				ans += nums[end--];
			else
				ans -= nums[start++];
		}
		cout << ans << "\n";
	}
}