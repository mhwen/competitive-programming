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
		ll m;
		cin >> n >> m;
		vector<ll> nums(n);
		ll greatest = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			greatest = max(greatest, nums[i]);
		}
		ll needed = 0;
		ll biggestDiff = 0;
		for(int i = 0; i < n; i++) {
			needed += greatest-nums[i];
			biggestDiff = max(biggestDiff, greatest-nums[i]);
		}
		cout << max(biggestDiff, (needed+m-1)/m) << "\n";
	}
}