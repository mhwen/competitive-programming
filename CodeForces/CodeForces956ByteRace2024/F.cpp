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
		vector<int> nums(n);
				
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		
		auto check = [&](int val) {
			set<pair<int, int>> curr;
			multiset<int> best;
			
			auto add = [&](int i) {
				pair<int, int> p = {nums[i], i};
				auto above = curr.lower_bound(p);
				if(above != curr.end()) {
					best.insert(above->first^p.first);
				}
				if(above != curr.begin()) {
					auto below = prev(above);
					best.insert(below->first^p.first);
				}
				if(above != curr.end() && above != curr.begin()) {
					auto below = prev(above);
					best.erase(best.find(above->first^below->first));
				}
				curr.insert(p);
			};
			
			auto remove = [&](int i) {
				pair<int, int> p = {nums[i], i};
				curr.erase(p);
				auto above = curr.lower_bound(p);
				if(above != curr.end()) {
					best.erase(best.find(above->first^p.first));
				}
				if(above != curr.begin()) {
					auto below = prev(above);
					best.erase(best.find(below->first^p.first));
				}
				if(above != curr.end() && above != curr.begin()) {
					auto below = prev(above);
					best.insert(above->first^below->first);
				}
			};
			
			
			ll count = 0;
			int right = 0;
			for(int i = 0; i < n; i++) {
				if(i > 0)
					remove(i-1);
				while(right < n && (best.empty() || *best.begin() > val))
					add(right++);
				if(!best.empty() && *best.begin() <= val)
					count += n-right+1;
			}
			return count;
		};
		

		int left = 0, right = 2e9;
		while(left <= right) {
			int mid = left+(right-left)/2;
			if(check(mid) < k)
				left = mid+1;
			else
				right  = mid-1;
		}
		cout << left << "\n";
	}
}