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
		int best = nums[n-1]-nums[0];
		for(int i = 0; i < n-1; i++) {
			best = max(best, nums[i]-nums[i+1]);
		}
		for(int i = 1; i < n; i++) {
			best = max(best, nums[i]-nums[0]);
		}
		for(int i = 0; i < n-1; i++) {
			best = max(best, nums[n-1]-nums[i]);
		}
		cout << best << "\n";
		
	}
	
}