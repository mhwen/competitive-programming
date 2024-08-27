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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int k;
		cin >> k;
		vector<int> sizes(k);
		for(int i = 0; i < k; i++) {
			cin >> sizes[i];
			for(int j = 0; j < sizes[i]-1; j++) {
				int a;
				cin >> a;
			}
		}
		int ans = 0;
		sort(all(sizes));
		reverse(all(sizes));
		for(int i : sizes) {
			int oldAns = ans;
			ans = max(ans, oldAns|i);
			for(int bit = 0; bit < 25; bit++) {
				if((1<<bit)&i) {
					int newVal = i-(1<<bit);
					newVal |= (1<<bit)-1;
					ans = max(ans, oldAns|newVal);
				}
			}
		}
		cout << ans << "\n";
	}
}