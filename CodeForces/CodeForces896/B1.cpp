#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	map<ll, pair<int, int>> possible;
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			ll num1 = 1LL << i;
			ll num2 = 1LL << j;
			// if(possible.count(num1-num2))
				// cout << i << " " << j;
			possible[num1-num2] = {num1, num2};
			// cout << num1 << " " << num2 << " " << num1-num2 << endl;
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		ll sum = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			sum += nums[i];
		}
		if(sum%n != 0)
			cout << "NO\n";
		else {
			ll needed = sum/n;
			map<ll, int> gives;
			map<ll, int> takes;
			bool bad = false;
			for(int i = 0; i < n; i++) {
				ll diff = needed-nums[i];
				// cout << "mean " << diff << endl;
				if(!possible.count(diff)) {
					bad = true;
					break;
				}
				if(diff == 0) {
					continue;
				}
				ll give = possible[diff].second;
				ll take = possible[diff].first;
				// cout << give << " " << take << endl;
				// if(give > nums[i]) {
					// bad = true;
					// break;
				// }
				gives[give]++;
				takes[take]++;
			}
			for(auto i : gives) {
				ll key = i.first;
				int amount = i.second;
				// cout << key << " " << amount << endl;
				if(takes[key] != amount) {
					// cout << "bad" << endl;
					bad = true;
					break;
				}
			}
			if(bad)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
}