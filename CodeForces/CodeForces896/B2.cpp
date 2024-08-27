#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	map<ll, pair<int, int>> possible;
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			ll num1 = 1LL << i;
			ll num2 = 1LL << j;
			if(i == j)
				continue;
			possible[num1-num2] = {num1, num2};
		}
	}
	set<ll> twoPows;
	for(int i = 0; i < 32; i++) {
		twoPows.insert(1LL << i);
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		ll sum = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			sum += nums[i];
		}
		if(sum%n != 0)
			cout << "NO\n";
		else {
			map<ll, int> powers;
			ll needed = sum/n;
			map<ll, int> needs;
			map<ll, int> giveTwos;
			map<ll, int> takeTwos;
			bool bad = false;
			for(int i = 0; i < n; i++) {
				ll diff = needed-nums[i];
				// cout << "needed " << diff << endl;
				if(diff == 0) {
					continue;
				}
				if(twoPows.count(diff)) {
					takeTwos[diff]++;
					continue;
				}
				else if(twoPows.count(-diff)) {
					giveTwos[-diff]++;
					continue;
				}
				
				if(!possible.count(diff)) {
					bad = true;
					break;
				}

				ll give = possible[diff].second;
				ll take = possible[diff].first;
				// cout << take << " " << give << endl;
				needs[give]--;
				needs[take]++;
			}
		
			
			for(int i = 30; i >= 0; i--) {
				ll val = 1LL<<i;
				needs[val] += takeTwos[val]-giveTwos[val];
				if(i == 0)
					break;
				if(needs[val] < 0) {
					int amnt = -needs[val];
					if(takeTwos[val>>1] < amnt) {
						bad = true;
						break;
					}
					takeTwos[val>>1] -= amnt;
					needs[val>>1] -= amnt;
				}
				else if(needs[val] > 0) {
					int amnt = needs[val];
					if(giveTwos[val>>1] < amnt) {
						bad = true;
						break;
					}
					giveTwos[val>>1] -= amnt;
					needs[val>>1] += amnt;
				}
			}
			
			if(needs[0] != 0)
				bad = true;
			
			
			if(bad)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
}