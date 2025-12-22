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
		cin >> n;
		vector<int> nums(n);
		vector<int> comp(n, 1);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		for(int i = n-2; i >= 0; i--) {
			if(nums[i] == nums[i+1])
				comp[i] = comp[i+1]+1;
		}
		
		vector<vector<int>> g(30, vector<int>(n));
		for(int i = 0; i < n-1; i++)
			g[0][i] = abs(nums[i+1]-nums[i]);
		for(int bit = 1; bit < 30; bit++) {
			for(int i = 0; i < n; i++) {
				g[bit][i] = gcd(g[bit-1][i], g[bit-1][min(i+(1<<(bit-1)), n-1)]);
			}
		}
			
		set<int> twoPows;
		int pow = 1;
		for(int i = 0; i < 30; i++) {
			twoPows.insert(pow);
			pow *= 2;
		}
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			int GCD = 0;
			ans += comp[i];
			int curr = i+comp[i]-1;
			for(int bit = 29; bit >= 0 && curr <= n; bit--) {
				auto newGcd = gcd(GCD, g[bit][curr]);
				if(!twoPows.count(newGcd)) {
					curr += (1<<bit);
					curr = min(curr, n+1);
					GCD = newGcd;
				}
			}
			ans += max(0, n-curr-1);
		}
		cout << ans << "\n";
	}
}