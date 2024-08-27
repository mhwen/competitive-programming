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
	map<ll, queue<int>> seen;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		seen[nums[i]].push(i+1);
	}
	int below = 0;
	ll curr = 0;
	vector<int> diffs(n-1);
	for(int i = 1; i < n; i++) {
		curr += nums[i]-nums[i-1];
		diffs[i-1] = nums[i]-nums[i-1];
		if(curr > 0)
			below++;
	}
	
	sort(nums.begin(), nums.end());
	ll start = nums[below];
	vector<int> ans;
	bool good = true;
	ans.push_back(seen[start].front());
	seen[start].pop();
	for(int i = 0; i < n-1; i++) {
		start -= diffs[i];
		if(seen[start].empty()) {
			good = false;
			break;
		}
		ans.push_back(seen[start].front());
		seen[start].pop();
	}
	if(good) {
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
	else {
		cout << -1 << "\n";
	}
	
}