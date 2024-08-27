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
			 

		vector<ll> ops;
		auto process = [&](ll val) {
			ops.push_back(val);
			for(int i = 0; i < n; i++)
				nums[i] = abs(nums[i]-val);
		};
		for(int steps = 0; steps < 39; steps++) {
			ll m = *max_element(all(nums));
			process(m/2);
		}
		ll m = *max_element(all(nums));
		process(m);
		if(*max_element(all(nums)) > 0)
			cout << -1 << "\n";
		else {
			cout << sz(ops) << "\n";
			for(ll l : ops)
				cout << l << " ";
			cout << "\n";
		}
	}
}