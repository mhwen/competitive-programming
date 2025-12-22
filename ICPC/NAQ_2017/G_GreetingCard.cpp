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

ll dx[4] = {0, 1118, 1680, 2018};
ll dy[4] = {2018, 1680, 1118, 0};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<pair<ll, ll>> directions;
	for(int i = 0; i < 4; i++) {
		directions.emplace_back(dx[i], dy[i]);
		directions.emplace_back(-dx[i], dy[i]);
		directions.emplace_back(dx[i], -dy[i]);
		directions.emplace_back(-dx[i], -dy[i]);
	}
	sort(all(directions));
	directions.erase(unique(all(directions)), directions.end());
	int n;
	cin >> n;
	set<pair<ll, ll>> seen;
	for(int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		seen.insert({x, y});
	}
	ll cnt = 0;
	for(auto [a, b] : seen) {
		for(auto [x, y] : directions) {
			if(seen.count({a+x, b+y})) {
				cnt++;
			}
		}
	}
	cout << cnt/2 << "\n";
	
}