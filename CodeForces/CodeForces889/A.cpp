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
		int negs = 0, pos = 0;
		int smallest = 100;
		int sId = -1;
		int biggest = -100;
		int bId = -1;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			if(nums[i] < 0)
				negs++;
			if(nums[i] > 0)
				pos++;
			if(smallest > nums[i]) {
				smallest = nums[i];
				sId = i;
			}
			if(biggest < nums[i]) {
				biggest = nums[i];
				bId = i;
			}
		}
		vector<pair<int, int>> moves;
		if(pos == 0) {
			for(int i = n-1; i >= 1; i--) {
				moves.push_back({i, i+1});
			}
		}
		else if(negs == 0) {
			for(int i = 2; i <= n; i++) {
				moves.push_back({i, i-1});
			}
		}
		else if(abs(smallest) < abs(biggest)) {
			if(negs <= 12) {
				for(int i = 0; i < n; i++) {
					if(nums[i] < 0) {
						moves.push_back({i+1, bId+1});
					}
				}
				for(int i = 2; i <= n; i++) {
					moves.push_back({i, i-1});
				}
			}
			else {
				for(int i = 0; i < 5; i++) {
					moves.push_back({sId+1, sId+1});
				}
				for(int i = 0; i < n; i++) {
					if(nums[i] > 0) {
						moves.push_back({i+1, sId+1});
					}
				}
				for(int i = n-1; i >= 1; i--) {
					moves.push_back({i, i+1});
				}
			}
		}
		else {
			if(pos <= 12) {
				for(int i = 0; i < n; i++) {
					if(nums[i] > 0) {
						moves.push_back({i+1, sId+1});
					}
				}
				for(int i = n-1; i >= 1; i--) {
					moves.push_back({i, i+1});
				}
			}
			else {
				for(int i = 0; i < 5; i++) {
					moves.push_back({bId+1, bId+1});
				}
				for(int i = 0; i < n; i++) {
					if(nums[i] < 0) {
						moves.push_back({i+1, bId+1});
					}
				}
				for(int i = 2; i <= n; i++) {
					moves.push_back({i, i-1});
				}
			}
		}
		cout << moves.size() << "\n";
		for(auto m : moves) {
			cout << m.first << " " << m.second << "\n";
			nums[m.first-1] += nums[m.second-1];
		}
		// for(int i : nums) {
			// cout << i << " ";
		// }
		// cout << endl;
	}
}