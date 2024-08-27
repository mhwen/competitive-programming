#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <random>
#include <chrono>

using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randval(int n) {
	return uniform_int_distribution(0, n-1)(rng);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	
	ll best = n;
	
	set<ll> seen;
	for(int j = 0; j < 50; j++) {
		int id = randval(n);
		
		for(int diff = -1; diff <= 1; diff++) {
			
			ll val = nums[id]+diff;
			if(val == 0)
				continue;
			vector<ll> factors;
			for(ll i = 2; i*i <= val; i++) {
				if(val%i==0) {
					factors.push_back(i);
					while(val%i==0)
						val/=i;
				}
			}
			if(val > 1)
				factors.push_back(val);
				
			for(ll f : factors) {
				if(seen.count(f))
					continue;
				seen.insert(f);
				ll cost = 0;
				for(ll num : nums) {
					if(num <= f) {
						cost += f-num;
					}
					else {
						cost += min(num%f, f-num%f);
					}
					if(cost >= best) {
						break;
					}
				}
				best = min(best, cost);
			}
		}
		
	}
	
	cout << best << "\n";
	
}