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
		ll sum = 0;
		int ones = 0;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			sum += a;
			if(a == 1)
				ones++;
		}
		sum -= ones*2+n-ones;
		if(n == 1 || sum < 0) {
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
		}
	}
}