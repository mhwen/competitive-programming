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

constexpr ll MOD = 998244353;

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
		map<ll, ll> spots;
		spots[0] = 1;
		for(int i = 0; i < n; i++) {
			map<ll, ll> newSpots;
			for(auto [val, ways] : spots) {
				newSpots[val+nums[i]] += ways;
				newSpots[val+nums[i]] %= MOD;
				newSpots[abs(val+nums[i])] += ways;
				newSpots[abs(val+nums[i])] %= MOD;
			}
			
			
			spots.clear();
			if(sz(newSpots) == 1)
				spots = newSpots;
			else {
				auto lowest = newSpots.begin();
				auto highest = newSpots.rbegin();
				spots[lowest->first] = lowest->second;
				spots[highest->first] = highest->second;
			}
		}
		cout << spots.rbegin()->second << "\n";
	}
}