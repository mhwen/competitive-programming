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
ll constexpr INF = 2e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll x, y;
		cin >> n >> x >> y;
		ll minX = INF, minY = INF;
		for(int i = 0; i < n; i++) {
			ll a, b, c;
			cin >> a >> b >> c;
			//ax + by <= c
			ll neededX = (c-b)/a;
			minX = min(minX, neededX);
			ll neededY = (c-a)/b;
			minY = min(minY, neededY);
		}
		ll cost1 = x-1+max(0LL, y-minY);
		ll cost2 = y-1+max(0LL, x-minX);
		cout << min(cost1, cost2) << "\n";
	}
}