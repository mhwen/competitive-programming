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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ifstream cin("clocktree.in");
	ofstream cout("clocktree.out");
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<vector<int>> con(n);
	int oddCnt = 0, evenCnt = 0;
	int oddSum = 0, evenSum = 0;
	for(int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		con[u].push_back(v);
		con[v].push_back(u);
	}
	function<void(int, int, int)> dfs = [&](int curr, int prev, int p) {
		if(p) {
			oddCnt++;
			oddSum += a[curr];
		}
		else {
			evenCnt++;
			evenSum += a[curr];
		}
		for(int next : con[curr])
			if(next != prev)
				dfs(next, curr, p^1);
	};
	dfs(0, 0, 0);
	int ans = 0;
	oddSum %= 12;
	evenSum %= 12;
	if((oddSum+1)%12==evenSum || oddSum==evenSum)
		ans += evenCnt;
	if((evenSum+1)%12==oddSum || evenSum==oddSum)
		ans += oddCnt;
	cout << ans << "\n";
}