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
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		if(n == 4) {
			if(nums[0]+nums[1] == nums[2]+nums[3])
				cout << "NO\n";
			else
				cout << "YES\n";
		}
		else {
			sort(nums.begin(), nums.end());
			if(nums[0] == nums[n-1])
				cout << "NO\n";
			else
				cout << "YES\n";
		}

	}
}