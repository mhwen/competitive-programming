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
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		if(n %2 == 1) {
			cout << "YES\n";
		}
		else {
			ll diff = 0;
			for(int i = 0; i < n-1; i++) {
				if(i%2 == 0) {
					diff += nums[i+1]-nums[i];
				}
			}
			if(diff < 0)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
}