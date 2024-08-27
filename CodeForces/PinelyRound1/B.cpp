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
		bool same1 = true, same2 = true;
		for(int i = 0; i+2 < n; i+=2) {
			if(nums[i] != nums[i+2])
				same1 = false;
		}
		for(int i = 1; i+2 < n; i+=2) {
			if(nums[i] != nums[i+2])
				same2 = false;
		}
		if(n > 2 && same1 && same2)
			cout << n/2+1 << "\n";
		else
			cout << n << "\n";
	}
}