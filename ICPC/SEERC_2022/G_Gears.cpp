#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> x(n);
	for(int i = 0; i < n; i++) {
		cin >> x[i];
	}
	vector<ll> r(n);
	ll smallestR = 2e9;
	for(int i = 0; i < n; i++) {
		cin >> r[i];
		smallestR = min(smallestR, r[i]);
	}
	int smallestEven = 0;
	ll currSum = 0;
	for(int i = 2; i < n; i+=2) {
		ll diff = x[i-1]-x[i-2]-(x[i]-x[i-1]);
		currSum += diff;
		if(currSum > 0) {
			smallestEven = i;
			currSum = 0;
		}
	}
	int smallestOdd = 1;
	currSum = 0;
	for(int i = 3; i < n; i+=2) {
		ll diff = x[i-1]-x[i-2]-(x[i]-x[i-1]);
		currSum += diff;
		if(currSum > 0) {
			smallestOdd = i;
			currSum = 0;
		}
	}
	vector<ll> ans(n);
	function<bool(int)> check = [&](int index) {
		map<ll, int> counts;
		for(ll l : r)
			counts[l]++;
		
		ll curr = smallestR;
		counts[smallestR]--;
		ans[index] = smallestR;
		if(counts[smallestR] == 0)
			counts.erase(smallestR);
		for(int i = index-1; i >= 0; i--) {
			ll needed = x[i+1]-x[i]-curr;
			if(counts.count(needed)) {
				counts[needed]--;
				if(counts[needed] == 0)
					counts.erase(needed);
				curr = needed;
				ans[i] = curr;
			}
			else {
				return false;
			}
		}
		curr = smallestR;
		for(int i = index+1; i < n; i++) {
			ll needed = x[i]-x[i-1]-curr;
			if(counts.count(needed)) {
				counts[needed]--;
				if(counts[needed] == 0)
					counts.erase(needed);
				curr = needed;
				ans[i] = curr;
			}
			else {
				return false;
			}
		}
		return true;
	};
	
	if(!check(smallestEven))
		check(smallestOdd);
		
	for(ll l : ans)
		cout << l << " ";
	cout << "\n";
	
}