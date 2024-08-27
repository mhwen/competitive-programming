#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		map<ll, ll> vals;
		vector<ll> nums(n);
		vector<bool> seen(n+1);
		int mex = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			seen[nums[i]] = true;
			while(seen[mex])
				mex++;
			vals[mex]++;
		}
		ll best = 0;
		ll curr = 0;
		for(auto k : vals) {
			curr += k.first*k.second;
		}
		best = max(best, curr);
		for(int i = 0; i < n; i++) {
			auto front = vals.begin()->first;
			curr -= front;
			vals[front]--;
			if(vals[front] == 0)
				vals.erase(front);
			
			ll lost = 0;
			auto back = vals.rbegin();
			while(!vals.empty() && back->first > nums[i]) {
				lost += back->second;
				curr -= back->first*back->second;
				vals.erase(back->first);
				back = vals.rbegin();
			}
			
			if(lost > 0) {
				vals[nums[i]] += lost;
				curr += nums[i]*lost;
			}
			
			curr += n;
			vals[n]++;
			
			best = max(best, curr);
			
		}
		
		cout << best << "\n";
	}
}