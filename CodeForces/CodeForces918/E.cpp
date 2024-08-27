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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		set<ll> seen;
		seen.insert(0);
		ll sum = 0;
		bool good = false;
		for(int i = 0; i < n; i++) {
			if(i%2==0)
				sum += nums[i];
			else
				sum -= nums[i];
			if(seen.count(sum)) {
				good = true;
			}
			seen.insert(sum);
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}