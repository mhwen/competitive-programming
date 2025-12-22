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
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		int l = 0, r = n-1;
		while(l < n && nums[l] == 0)
			l++;
		while(r >= 0 && nums[r] == 0)
			r--;
		if(l > r)
			cout << 0 << "\n";
		else {
			int ans = 1;
			for(int i = l; i <= r; i++) {
				if(nums[i] == 0) {
					ans++;
					break;
				}
			}
			cout << ans << "\n";
		}
	}
}