#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;


typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, m;
	ll c, d;
	cin >> n >> k >> m >> c >> d;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	Tree<pair<ll, int>> inVals;
	Tree<pair<ll, int>> outVals;
	for(int i = 0; i < m-1; i++) {
		inVals.insert({nums[i]+i*d+c, i});
	}
	for(int i = m-1; i < n; i++) {
		outVals.insert({nums[i], i});
	}
	
	function<bool(ll, ll)> check = [&](ll val, ll inOffset) {
		auto outCeil = outVals.lower_bound({val, -1});
		ll outSmaller = outVals.size();
		if(outCeil != outVals.end())
			outSmaller = outVals.order_of_key(*outCeil);
		ll outBigger = outVals.size()-outSmaller;
		
		auto inCeil = inVals.lower_bound({val+inOffset, -1});
		ll inSmaller = inVals.size();
		if(inCeil != inVals.end())
			inSmaller = inVals.order_of_key(*inCeil);
		ll inBigger = inVals.size()-inSmaller;
		
		return outBigger+inBigger >= k;
	};
	
	ll best = 0;
	ll inOffset = 0;
	for(int right = m-1; right < n; right++) {
		outVals.erase(outVals.find({nums[right], right}));
		inVals.insert({nums[right]+right*d+c, right});
		if(right >= m) {
			int left = right-m;
			outVals.insert({nums[left], left});
			inVals.erase({nums[left]+left*d+c, left});
		}
		// cout << "including " << right-m+1 << " to " << right << endl;
		// for(auto JJ : inVals)
			// cout << JJ.first << " ";
		// cout << endl;
		// for(auto JJ : outVals)
			// cout << JJ.first << " ";
		// cout << endl;
		ll l = 0, r = 1e16;
		while(l <= r) {
			ll mid = (l+r)/2;
			if(check(mid, inOffset)) {
				l = mid+1;
			}
			else {
				r = mid-1;
			}
		}
		best = max(best, r);
		inOffset += d;
	}
	cout << best << "\n";
}