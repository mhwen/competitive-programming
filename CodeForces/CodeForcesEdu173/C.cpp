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
		vector<ll> nums(n);
		int x = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(abs(nums[i]) != 1)
				x = i;
		}
		auto getRange = [&](int l, int r) {
			ll lo = 0, hi = 0;
			ll L = 0, H = 0;
			for(int i = l; i <= r; i++) {
				lo = min(lo+nums[i], nums[i]);
				hi = max(hi+nums[i], nums[i]);
				L = min(L, lo);
				H = max(H, hi);
			}
			return pair{L, H};
		};
		
		auto getPre = [&](int to) {
			ll curr = 0;
			ll lo = 0, hi = 0;
			for(int i = to; i >= 0; i--) {
				curr += nums[i];
				lo = min(lo, curr);
				hi = max(hi, curr);
			}
			return pair{lo, hi};
		};
		
		auto getSuf = [&](int to) {
			ll curr = 0;
			ll lo = 0, hi = 0;
			for(int i = to; i < n; i++) {
				curr += nums[i];
				lo = min(lo, curr);
				hi = max(hi, curr);
			}
			return pair{lo, hi};
		};
		
		vector<pair<ll, ll>> ranges;
		ranges.push_back(getRange(0, x-1));
		ranges.push_back(getRange(x+1, n-1));
		auto l = getPre(x-1);
		auto r = getSuf(x+1);
		ranges.push_back({l.first+r.first+nums[x], l.second+r.second+nums[x]});
		set<ll> ans;
		for(auto ra : ranges) {
			for(ll i = ra.first; i <= ra.second; i++)
				ans.insert(i);
		}
				
		cout << sz(ans) << "\n";
		for(ll a : ans)
			cout << a << " ";
		cout << "\n";
	}
}