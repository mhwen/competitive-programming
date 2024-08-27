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
		int ans = -1;
		for(int pos = 0; pos <= n; pos++) {
			int count = 0;
			for(int i : nums) {
				if(i > pos)
					count++;
			}
			if(count == pos) {
				ans = pos;
			}
		}
		cout << ans << "\n";
			
	}
}