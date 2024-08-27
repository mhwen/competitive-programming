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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		multiset<ll> nums;
		for(int i = 0; i < n; i++) {
			ll a;
			cin >> a;
			nums.insert(a);
		}
		vector<ll> ans;
		ll sum = 0;
		while(nums.upper_bound(sum) != nums.end()) {
			ll val = *nums.upper_bound(sum);
			sum += val;
			ans.push_back(val);
			nums.erase(nums.find(val));
		}
		cout << nums.size() << "\n";
		for(ll val : nums)
			ans.push_back(val);
		for(ll val : ans)
			cout << val << " ";
		cout << "\n";
	}
}