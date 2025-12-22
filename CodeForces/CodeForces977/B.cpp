#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll x;
		cin >> n >> x;
		map<ll, int> cnt;
		for(int i = 0; i < n; i++) {
			ll num;
			cin >> num;
			cnt[num]++;
		}
		int ans = 0;
		while(cnt[ans] > 0) {
			int add = cnt[ans]-1;
			cnt[ans+x] += add;
			ans++;
		}
		cout << ans << "\n";
	}
}