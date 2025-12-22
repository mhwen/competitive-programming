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
	int n;
	cin >> n;
	ld ans = 0;
	map<int, vector<int>> seen;
	for(int i = 0; i < n; i++) {
		int s, c;
		cin >> s >> c;
		seen[s].push_back(c);
	}
	for(auto& [s, c] : seen) {
		sort(all(c));
		for(int i = 0; i < sz(c)/2; i++) {
			ans += log(c[sz(c)-1-i])-log(c[i]);
		}
	}
	cout << fixed << setprecision(20) << ans << "\n";
}