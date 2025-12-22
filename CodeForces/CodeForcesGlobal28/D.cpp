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
#include <cassert>

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
		int n, m;
		cin >> n >> m;
		vector<int> a(n);
		vector<int> score(m);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		int kevin = a[0];
		sort(all(a));
		for(int i = 0; i < m; i++) {
			int b;
			cin >> b;
			if(b <= kevin)
				score[i] = 0;
			else
				score[i] = (int)(a.end()-lower_bound(all(a), b));
		}
		sort(all(score));
		for(int k = 1; k <= m; k++) {
			ll ans = 0;
			for(int i = k-1; i < m; i+=k)
				ans += score[i]+1;
			cout << ans << " ";
		}
		cout << "\n";
	}
}