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
constexpr ll MOD = 998244353;

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
		ll ans = 1;
		ll free = 0;
		ll extra = 0;
		ll prev = 0;
		for(int i = 0; i < n; i++) {
			ll diff = nums[i]-prev;
			prev = nums[i];
			if(diff == 0) {
				free++;
				extra++;
			}
			else if(diff == 1) {
				ans = (ans*(free+1)%MOD + ans*extra%MOD)%MOD;
			}
			else if(diff == 2) {
				ans = ans*free%MOD;
				ans = ans*extra%MOD;
				free--;
				extra--;
			}
			else {
				ans = 0;
			}
		}
		if(free > 0 || extra > 0)
			cout << 0 << "\n";
		else
			cout << ans << "\n";
	}
}