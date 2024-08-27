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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	while(true) {
		int n, m;
		cin >> n >> m;
		if(n == 0 && m == 0)
			break;
		set<int> seen;
		map<int, int> front;
		map<int, int> side;
		for(int i = 0; i < n; i++) {
			int h;
			cin >> h;
			front[h]++;
			seen.insert(h);
		}
		for(int i = 0; i < m; i++) {
			int h;
			cin >> h;
			side[h]++;
			seen.insert(h);
		}
		ll ans = 0;
		for(int i : seen) {
			ans += max(front[i], side[i])*i;
		}
		cout << ans << "\n";
	}
}