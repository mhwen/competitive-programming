#include <iostream>
#include <vector>
#include <algorithm>

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
		vector<ll> preSum(n+1);
		vector<int> nonOnes;
		vector<ll> nums(n);
		ll p = 1;
		bool takeAll = false;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(nums[i] > 1)
				nonOnes.push_back(i+1);
			preSum[i+1] = preSum[i]+nums[i];
			p *= nums[i];
			if(p > (ll)1e9)
				takeAll = true;
		}
		if(takeAll) {
			cout << nonOnes.front() << " " << nonOnes.back() << "\n";
		}
		else {
			int l = 1, r = 1;
			ll best = 0;
			for(int i = 0; i < (int)nonOnes.size(); i++) {
				ll prod = 1;
				for(int j = i; j < (int)nonOnes.size(); j++) {
					prod *= nums[nonOnes[j]-1];
					ll val = prod+preSum[n]-preSum[nonOnes[j]]+preSum[nonOnes[i]-1];
					if(val > best) {
						best = val;
						l = nonOnes[i];
						r = nonOnes[j];
					}
				}
			}
			cout << l << " " << r << "\n";
		}
	}
}