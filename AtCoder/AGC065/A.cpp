#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

//https://atcoder.jp/contests/agc065/tasks/agc065_a
using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> nums(n);
	map<ll, ll> seen;
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		seen[nums[i]%k]++;
	}
	ll start = nums[0];
	for(int i = 0; i < n; i++) {
		if(seen[nums[i]] > seen[start])
			start = nums[i];
	}
	ll smallest = 2e9;
	ll ans = 0;
	ll val = start;
	for(int i = 0; i < n-1; i++) {
		auto next = seen.upper_bound(val);
		if(next == seen.end())
			next = seen.begin();
		ll take = next->first;
		smallest = min(smallest, (val+k-take)%k);
		ans += (val+k-take)%k;
		seen[take]--;
		if(seen[take] == 0)
			seen.erase(take);
		val = take;
	}
	ll take = start;
	smallest = min(smallest, (val+k-take)%k);
	ans += (val+k-take)%k;
	cout << ans-smallest << "\n";
}