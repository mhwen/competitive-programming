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
typedef long double ld;
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
		vector<int> nums(n);
		for(int& i : nums)
			cin >> i;
		int ans = -1;
		for(int i = 1; i < n-1; i++) {
			if(nums[i] != nums[i-1] && nums[i]+1 != nums[i+1])
				ans = i+1;
		}
		cout << ans << "\n";
	}
}