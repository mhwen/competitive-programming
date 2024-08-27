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
		ll steps = 0;
		pair<int, int> curr = {-1, 0};
		for(int i = 0; i < n; i++) {
			auto nextAbove = remaining.lower_bound(curr);
			auto nextBelow = remaining.lower_bound({curr.first, 0});
			auto next = nextBelow;
			if(nextAbove == remaining.end())
				next = nextBelow;
			else if(nextAbove->first == curr.first)
				next = nextAbove;
			else if(nextAbove->first == nextBelow->first)
				next = nextAbove;
			else
				next = nextBelow;
			
			steps += (next->second-curr.second+n)%n;
			curr = *next;
			// cout << curr.first << " " << curr.second << endl;
			remaining.erase(next);
		}
		cout << steps << "\n";
	}
}