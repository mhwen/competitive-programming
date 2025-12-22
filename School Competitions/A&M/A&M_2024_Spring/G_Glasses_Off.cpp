#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	ll m = 0;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		m = max(m, nums[i]);
	}
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ans += max(0LL, m-1-nums[i]);
	}
	cout << ans << "\n";
}