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
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++)
	    cin >> nums[i];
	ll sum = accumulate(all(nums), 0LL);
	ll curr = 0;
	int ans = 0;
	for(int i = 0; i < n-1; i++) {
	    curr += nums[i];
	    if(curr*2==sum)
	        ans++;
	}
	cout << ans << "\n";
}