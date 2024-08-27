#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	vector<ll> left(n+2);
	for(int i = 1; i <= n; i++) {
		left[i] = max(left[i-1], nums[i-1]+n-i);
	}
	vector<ll> right(n+2);
	for(int i = n; i >= 1; i--) {
		right[i] = max(right[i+1], nums[i-1]+i-1);
	}
	ll best = 2e9;
	for(int i = 1; i <= n; i++) {
		best = min(best, max(left[i-1], max(nums[i-1], right[i+1])));
	}
	cout << best << "\n";

}