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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		sort(nums.rbegin(), nums.rend());
		nums.push_back(0);
		nums.erase(unique(nums.begin(), nums.end()), nums.end());
		vector<int> winner(sz(nums));
		winner[0] = 2;
		for(int i = 1; i < sz(nums); i++) {
			int diff = nums[i-1]-nums[i];
			if(winner[i-1] == 2)
				winner[i] = 1;
			else {
				if(diff>1)
					winner[i] = 1;
				else
					winner[i] = 2;
			}
		}
		if(winner.back() == 1)
			cout << "Alice\n";
		else
			cout << "Bob\n";
	}
}