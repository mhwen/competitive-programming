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
	int n, k;
	cin >> n >> k;
	vector<vector<int>> con(n);
	for(int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		con[p].push_back(i);
	}
	priority_queue<int> best;
	vector<int> ans(n);
	function<void(int)> dfs = [&](int curr) {
		if(sz(con[curr]) == 0) {
			ans[curr] = 1;
			return;
		}
		vector<int> me;
		for(int next : con[curr]) {
			dfs(next);
			me.push_back(ans[next]);
		}
		sort(all(me));
		for(int i = 0; i < sz(me)-1; i++)
			best.push(me[i]);
		ans[curr] = me.back()+1;
	};
	
	dfs(0);
	best.push(ans[0]);
	int a = 0;
	while(k > 0 && !best.empty()) {
		a += best.top();
		best.pop();
		k--;
	}
	cout << a << "\n";
}