#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int gcd(int a, int b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

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
		int ans = 0;
		
		for(int i = 0; i < n/2; i++) {
			ans = gcd(ans, abs(nums[i]-nums[n-i-1]));
		}
		
		cout << ans << "\n";
		
	}
}