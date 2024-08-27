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
		vector<int> down(n+1);
		vector<int> up(n+1);
		up[0] = 1;
		for(int i = 0; i < n-1; i++) {
			if(nums[i] <= nums[i+1])
				up[i+1]++;
			if(nums[i] >= nums[i+1])
				down[i+1]++;
		}
		for(int i = 0; i < n; i++) {
			up[i+1] += up[i];
		}
		for(int i = n; i > 0; i--) {
			down[i-1] += down[i];
		}
		int best = 1e9;
		for(int i = 1; i < n; i++) {
			best = min(best, up[i-1]+down[i+1]);
			// cout << i << " " << up[i-1]+down[i+1] << endl;
		}
		best = min(best, up[n]);
		best = min(best, down[0]);
		cout << best << "\n";
		
	}
}