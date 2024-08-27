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
	int n, m;
	cin >> n >> m;
	vector<pair<int, pair<int, int>>> order;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < m; c++) {
			int num;
			cin >> num;
			order.push_back({num, {r, c}});
		}
	}
	vector<bool> seen(n*n);
	vector<vector<int>> filled(m); 
	sort(order.rbegin(), order.rend());
	int ans = 0;
	
	auto id = [&](int a, int b) {
		if(a < b)
			swap(a, b);
		return a*n+b;
	};
	
	for(auto [val, coords] : order) {
		int r = coords.first;
		int c = coords.second;
		bool found = false;
		for(int R : filled[c]) {
			int I = id(r, R);
			if(seen[I]) {
				ans = val;
				found = true;
				break;
			}
			seen[I] = true;
		}
		filled[c].push_back(r);
		if(found)
			break;
	}
	cout << ans << "\n";
}