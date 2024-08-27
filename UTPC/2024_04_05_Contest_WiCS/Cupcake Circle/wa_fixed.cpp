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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		set<pair<int, int>> remaining;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			remaining.insert({nums[i], i});
		}
		sort(nums.begin(), nums.end());
		ll steps = 0;
		pair<int, int> curr = {-1, 0};
		for(int i = 0; i < n; i++) {
			pair<int, int> next;
			if(nums[i] == curr.first) {
				auto nextAbove = remaining.lower_bound(curr);
				auto nextBelow = remaining.lower_bound({curr.first, 0});
				if(nextAbove == remaining.end() || nextAbove->first != nums[i])
					next = *nextBelow;
				else
					next = *nextAbove;
			}
			else {
				auto nextAbove = remaining.lower_bound({nums[i], curr.second});
				auto nextBelow = remaining.lower_bound({nums[i], 0});
				if(nextAbove == remaining.end() || nextAbove->first != nums[i])
					next = *nextBelow;
				else
					next = *nextAbove;
			}
			
			steps += (next.second-curr.second+n)%n;
			curr = next;
			// cout << curr.first << " " << curr.second << endl;
			remaining.erase(next);
		}
		cout << steps << "\n";
	}
}