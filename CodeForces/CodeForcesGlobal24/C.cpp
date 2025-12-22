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
#include <cassert>

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
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		sort(all(nums));
		if(nums.front() == nums.back())
			cout << n/2 << "\n";
		else {
			ll best = 0;
			for(ll i = 0; i < (ll)n-1; i++)
				if(nums[i] != nums[i+1])
					best = max(best, (i+1)*(n-i-1));
			cout << best << "\n";
		}
	}
}