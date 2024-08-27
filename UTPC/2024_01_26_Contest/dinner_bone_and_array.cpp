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
			ll val;
			cin >> val;
			nums[i] = val*val*val;
		}
		ll smallest = 0, biggest = 0;
		for(int mask = 0; mask < (1<<n)-1; mask++) {
			ll sz = 0;
			ll sum = 0;
			for(int bit = 0; bit < n; bit++) {
				if(mask&(1<<bit)) {
					sz++;
					sum += nums[bit];
				}
			}
			if(sz%2)
				sz = -sz;
			smallest = min(smallest, sum*sz);
			biggest = max(biggest, sum*sz);
		}
		cout << smallest << " " << biggest << "\n";
	}
}