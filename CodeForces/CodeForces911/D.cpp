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
	vector<vector<int>> factors(1e5+1);
	for(int i = 1; i <= 1e5; i++) {
		for(int j = i; j <= 1e5; j+=i)
			factors[j].push_back(i);
	}
	
	vector<vector<vector<int>>> subtract(1e5+1);
	for(int i = 1; i <= 1e5; i++) {
		reverse(factors[i].begin(), factors[i].end());
		subtract[i].resize(factors[i].size());
		for(int j = 0; j < (int)factors[i].size(); j++) {
			for(int h = j+1; h < (int)factors[i].size(); h++) {
				if(factors[i][j]%factors[i][h]==0)
					subtract[i][j].push_back(h);
			}
		}
	}
	
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		sort(nums.begin(), nums.end());
		ll prev = 0;
		ll prevContribution = 0;
		ll ans = 0;
		vector<ll> counts(1e5+1);
		for(int i = 0; i < n; i++) {
			ll contribution = 0;
			if(nums[i] == prev) {
				contribution = (prevContribution/(n-i)+nums[i])*(n-i-1);
			}
			else {
				vector<ll> myCounts(factors[nums[i]].size());
				for(int j = 0; j < (int)factors[nums[i]].size(); j++) {
					int f = factors[nums[i]][j];
					myCounts[j] += counts[f];
					for(int index : subtract[nums[i]][j]) {
						myCounts[index] -= myCounts[j];
					}
					contribution += myCounts[j]*factors[nums[i]][j]*(n-i-1);
				}
			}
			ans += contribution;
			
			for(int f : factors[nums[i]])
				counts[f]++;
			prev = nums[i];
			prevContribution = contribution;
		}
		cout << ans << "\n";
	}
}