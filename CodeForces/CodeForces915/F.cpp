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
typedef pair<int, int> pii;
typedef vector<int> vi;
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
		vi nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			nums[i]--;
		}
		vector<pii> left(n);
		vector<pii> right(n);
		pii l{-1, -1};
		for(int i = 0; i < n; i++) {
			left[i] = l;
			l = max(l, max(pair{nums[i], l.first}, pair{l.first, nums[i]}));
		}
		pii r{n, n};
		for(int i = n-1; i >= 0; i--) {
			right[i] = r;
			r = min(r, min(pair{nums[i], r.first}, pair{r.first, nums[i]}));
		}
		int good = 0;
		map<pii, int> fix;
		int gain = 0;
		for(int i = 0; i < n; i++) {
			if(left[i].second > i || right[i].second < i)
				continue;
			vector<int> bad;
			if(nums[i] != i)
				bad.push_back(nums[i]);
			if(left[i].first >= i)
				bad.push_back(left[i].first);
			if(right[i].first <= i)
				bad.push_back(right[i].first);
			assert(sz(bad) != 1);
			if(sz(bad) == 0)
				good++;
			else if(sz(bad) == 2) {
				int a = min(bad[0], bad[1]);
				int b = max(bad[0], bad[1]);
				fix[{a, b}]++;
				gain = max(gain, fix[{a, b}]);
			}
		}
		if(good == n)
			cout << good-2 << "\n";
		else
			cout << good+gain << "\n";
	}
}