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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		for(int i = 0; i < n; i++) {
			int p;
			cin >> p;
			p--;
			if(i == 0)
				continue;
			con[p].push_back(i);
		}
		int greatest = 0;
		vector<int> ans(n);
		function<void(int)> dfs = [&](int curr) {
			vector<int> sizes;
			for(int next : con[curr]) {
				dfs(next);
				sizes.push_back(ans[next]);
			}
			sort(sizes.rbegin(), sizes.rend());
			if(sz(sizes) == 0) {
				ans[curr] = 1;
			}
			else if(sz(sizes) == 1) {
				ans[curr] = sizes[0];
			}
			else {
				ans[curr] = max(sizes[0], sizes[1]+1);
			}
			greatest = max(greatest, ans[curr]);
		};
		dfs(0);
		cout << greatest << "\n";
	}
}