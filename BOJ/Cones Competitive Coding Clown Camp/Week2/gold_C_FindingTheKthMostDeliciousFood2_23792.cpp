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
	int n;
	cin >> n;
	vector<vector<ll>> food(3, vector<ll>(n));
	map<ll, pair<int, int>> ids;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			cin >> food[i][j];
			ids[food[i][j]] = {i+1, j+1};
		}
	}
	
	auto count = [&](int id, ll val, int ceil) {
		auto it = upper_bound(all(food[id]), val);
		return min(ceil, (int)(it-food[id].begin()));
	};
	
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int x, y, z, k;
		cin >> x >> y >> z >> k;
		ll left = 0, right = 3e9;
		while(left <= right) {
			ll mid = (left+right)/2;
			ll amt = count(0, mid, x)+count(1, mid, y)+count(2, mid, z);
			if(amt < k)
				left = mid+1;
			else
				right = mid-1;
		}
		auto ans = ids[left];
		cout << ans.first << " " << ans.second << "\n";
	}

	
}