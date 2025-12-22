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
		ll k;
		cin >> n >> k;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		sort(all(nums));
		reverse(all(nums));
		ll score = 0;
		for(int i = 0; i < n; i++) {
			if(i%2)
				score -= nums[i];
			else
				score += nums[i];
		}
		ll extra = 0;
		for(int i = 1; i < n; i+=2) {
			extra += nums[i-1]-nums[i];
		}
		cout << score-min(extra, k) << "\n";
	}
}