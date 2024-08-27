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

int gcd(int a, int b) {
	if(b==0)
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
		int count = 1;
		for(int k = 1; k < n; k++) {
			if(n%k==0) {
				int GCD = abs(nums[0]-nums[k]);
				for(int i = 1; i+k<n; i++) {
					int diff = abs(nums[i]-nums[i+k]);
					GCD = gcd(GCD, diff);
				}
				if(GCD != 1)
					count++;
			}
		}
		cout << count << "\n";
	}

}