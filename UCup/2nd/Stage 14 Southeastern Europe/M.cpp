#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll queryMin(int a, int b, vector<vector<ll>>& table) {
	int dep = 31 - __builtin_clz(b - a);
	return min(table[dep][a], table[dep][b-(1<<dep)]);
}

ll queryMax(int a, int b, vector<vector<ll>>& table) {
	int dep = 31 - __builtin_clz(b - a);
	return max(table[dep][a], table[dep][b-(1<<dep)]);
}

ll queryDiff(int l, int r, vector<vector<ll>>& mins, vector<vector<ll>>& maxes) {
	return queryMax(l, r, maxes)-queryMin(l, r, mins);
}

bool check(ll range, vector<ll>& nums, vector<vector<ll>>& mins, vector<vector<ll>>& maxes) {
	int n = (int)nums.size();
	int right = 0;
	while(right < n && queryDiff(0, right+1, mins, maxes) <= range) {
		right++;
	}
	if(right == n)
		return true;
	for(int left = 1; left < n; left++) {
		while(right < n && queryDiff(left, right+1, mins, maxes) <= range) {
			right++;
		}
		ll diff = queryDiff(0, left, mins, maxes);
		if(right < n) {
			ll leftMin = queryMin(0, left, mins);
			ll leftMax = queryMax(0, left, maxes);
			ll rightMin = queryMin(right, n, mins);
			ll rightMax = queryMax(right, n, maxes);
			diff = max(leftMax, rightMax)-min(leftMin, rightMin);
		}
		if(diff <= range)
			return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);

		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<vector<ll>> mins(1, nums);
		vector<vector<ll>> maxes(1, nums);
		
		for(int pw = 1, k = 1; pw*2 <= n; pw*=2, k++) {
			mins.emplace_back(n-pw*2+1);
			maxes.emplace_back(n-pw*2+1);
			for(int j = 0; j < (int)mins[k].size(); j++) {
				mins[k][j] = min(mins[k-1][j], mins[k-1][j+pw]);
				maxes[k][j] = max(maxes[k-1][j], maxes[k-1][j+pw]);
			}
		}
		
		ll left = 0, right = 1e9;
		while(left <= right) {
			ll mid = (left+right)/2;
			if(check(mid, nums, mins, maxes)) {
				right = mid-1;
			}
			else {
				left = mid+1;
			}
		}
		cout << left << "\n";
		
	}
}