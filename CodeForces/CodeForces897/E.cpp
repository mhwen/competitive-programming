#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		int ans = 0;
		for(int i = 1; i+k-1<=n; i+=k) {
			cout << "? " << i << endl;
			int a;
			cin >> a;
			ans ^= a;
		}
		if(n%k!=0) {
			int extra = n%k;
			int a;
			cout << "? " << n-k-extra/2+1 << endl;
			cin >> a;
			ans ^= a;
			cout << "? " << n-k+1 << endl;
			cin >> a;
			ans ^= a;
		}
		cout << "! " << ans << endl;
	}
}