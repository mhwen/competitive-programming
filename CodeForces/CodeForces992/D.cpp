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
#include <cassert>

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
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<int> ans(n);
		int id = 1;
		function<void(int, int)> dfs = [&](int curr, int prev) {
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				while(true) {
					if(id-ans[curr]==1)
						break;
					if(id-ans[curr]>2&&(id-ans[curr])%2==0)
						break;
					id++;
				}
				ans[next] = id++;
				dfs(next, curr);
			}
		};
		ans[0] = 1;
		dfs(0, -1);
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}