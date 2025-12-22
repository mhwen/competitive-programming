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
		int n, a, b;
		cin >> n >> a >> b;
		int incr = gcd(a, b);
		vector<int> mods(n);
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			mods[i] = num%incr;
		}
		sort(all(mods));
		int best = mods.back()-mods.front();
		for(int i = 0; i < n-1; i++) {
			best = min(best, mods[i]+incr-mods[i+1]);
		}
		cout << best << "\n";
	}
}