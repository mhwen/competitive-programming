#include <iostream>
#include <vector>

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
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<int> twoBest(n);
		int best = nums[0];
		for(int i = 1; i < n; i++) {
			best--;
			twoBest[i] = nums[i]+best;
			best = max(best, nums[i]);
		}
		// for(int i : twoBest)
			// cout << i << " ";
		// cout << endl;
		vector<int> threeBest(n);
		best = twoBest[1];
		int ans = 0;
		for(int i = 2; i < n; i++) {
			best--;
			threeBest[i] = nums[i]+best;
			ans = max(ans, threeBest[i]);
			best = max(best, twoBest[i]);
		}
		// for(int i : threeBest)
			// cout << i << " ";
		// cout << endl;
		cout << ans << "\n";
	}
}