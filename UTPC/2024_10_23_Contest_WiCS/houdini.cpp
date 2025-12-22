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
	vector<int> p(n);
	for(int i = 0; i < n; i++) {
		cin >> p[i];
		p[i] %= 2;
	}
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	
	int ans = 1;
	
	function<int(int, int)> dfs = [&](int curr, int prev) {
		int tot = p[curr];
		for(int next : con[curr]) {
			if(next != prev)
				tot += dfs(next, curr);
		}
		tot %= 2;
		if(tot==0 && curr != 0)
			ans++;
		return tot;
	};
	
	if(dfs(0, -1) == 1)
		ans = -1;
	cout << ans << "\n";
	
}