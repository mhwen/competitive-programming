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
		int l, r;
		cin >> l >> r;
		int count = 1;
		int res = 1;
		while(l*res*2<=r) {
			res *= 2;
			count++;
		}
		int max2 = r/res;
		int res3 = res*3/2;
		int max3 = r/res3;
		int ans = (max2-l+1) + (count-1)*max(0, max3-l+1);
		cout << count << " " << ans << "\n";
	}
}