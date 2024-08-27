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
		vector<pair<int, int>> moves;
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			nums[i]--;
		}
		for(int i = 0; i < n; i++) {
			if(nums[i] != i) {
				int right = -1;
				for(int j = i+1; j < n; j++) {
					if(nums[j] < nums[i])
						right = j;
				}
				moves.push_back({i+1, right+1});
				sort(nums.begin()+i, nums.begin()+right+1);
			}
		}
		cout << sz(moves) << "\n";
		for(auto[l, r] : moves)
			cout << l << " " << r << "\n";
	}
}