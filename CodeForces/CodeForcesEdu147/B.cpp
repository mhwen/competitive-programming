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
		vector<int> a(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		int left = n, right = 0;
		for(int i = 0; i < n; i++) {
			if(nums[i] != a[i])
				right = i;
		}
		for(int i = n-1; i >= 0; i--) {
			if(nums[i] != a[i])
				left = i;
		}
		while(left > 0 && a[left-1] <= a[left])
			left--;
		while(right < n-1 && a[right+1] >= a[right])
			right++;
		cout << left+1 << " " << right+1 << "\n";
	}
}