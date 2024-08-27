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
		cin >> n;
		vector<ll> nums(n);
		vector<ll> evens;
		ll odd = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(nums[i]%2==0)
				evens.push_back(nums[i]);
			else
				odd = max(odd, nums[i]);
		}
		if(sz(evens) == n)
			cout << 0 << "\n";
		else {
			bool bad = false;
			sort(all(evens));
			for(int i = 0; i < sz(evens); i++) {
				if(odd > evens[i])
					odd += evens[i];
				else
					bad = true;
			}
			if(bad)
				cout << sz(evens)+1 << "\n";
			else
				cout << sz(evens) << "\n";
		}
	}
}