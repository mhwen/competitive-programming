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
		vector<vector<int>> pos(n+1);
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			pos[nums[i]].push_back(i);
		}

		vector<vector<int>> swaps(n);
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < (int)pos[i].size(); j++) {
				swaps[j].push_back(pos[i][j]);
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < (int)swaps[i].size()-1; j++) {
				swap(nums[swaps[i][j]], nums[swaps[i][j+1]]);
			}
		}
		for(int i : nums)
			cout << i << " ";
		cout << "\n";
	}
}