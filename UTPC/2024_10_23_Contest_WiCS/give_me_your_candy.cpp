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

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums(n);
	vector<int> isFav(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	for(int i = 0; i < n; i++)
		cin >> isFav[i];
	ll sum = accumulate(all(nums), 0LL);
	vector<ll> p(n);
	ll curr = nums[0];
	for(int i = 1; i < n; i++) {
		p[i] = min(p[i-1], curr);
		curr += nums[i];
	}
	vector<ll> s(n);
	curr = nums[n-1];
	for(int i = n-2; i >= 0; i--) {
		s[i] = min(s[i+1], curr);
		curr += nums[i];
	}
	ll best = -INF;
	for(int i = 0; i < n; i++) {
		if(isFav[i])
			best = max(best, sum-p[i]-s[i]);
	}
	cout << best << "\n";
	
}