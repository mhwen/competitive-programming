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
		vector<int> nums(n);
		int smallest = 2e9;
		int smallestId = n;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(nums[i] < smallest) {
				smallest = nums[i];
				smallestId = i;
			}
		}
		int sortedId = n-1;
		for(int i = n-2; i >= 0; i--) {
			if(nums[i] > nums[i+1])
				break;
			sortedId = i;
		}
		if(sortedId == smallestId)
			cout << smallestId << "\n";
		else
			cout << -1 << "\n";
	}
}