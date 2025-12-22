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
	map<string, int> id;
	vector<ld> speed(n);
	int Id = 0;
	int root = -1;
	vector<vector<int>> con(n);
	for(int i = 0; i < n; i++) {
		string child, par;
		ld S;
		cin >> child >> S >> par;
		if(!id.count(child))
			id[child] = Id++;
		int c = id[child];
		speed[c] = S;
		if(par == "CEO") {
			root = c;
		}
		else {
			if(!id.count(par))
				id[par] = Id++;
			int p = id[par];
			con[p].push_back(c);
		}
	}
	vector<pair<int, ld>> used(n);
	vector<pair<int, ld>> unused(n);
	function<void(int)> dfs = [&](int curr) {
		pair<int, ld> use = {0, 0};
		pair<int, ld> unuse = {0, 0};
		for(int next : con[curr]) {
			dfs(next);
			auto best = max(used[next], unused[next]);
			unuse.first += best.first;
			unuse.second += best.second;
		}
		for(int next : con[curr]) {
			auto matchLose = max(used[next], unused[next]);
			pair<int, ld> matchGain = {unused[next].first+1, unused[next].second+min(speed[curr], speed[next])};
			auto val = unuse;
			val.first -= matchLose.first;
			val.second -= matchLose.second;
			val.first += matchGain.first;
			val.second += matchGain.second;
			use = max(use, val);
		}
		used[curr] = use;
		unused[curr] = unuse;
	};
	dfs(root);
	auto ans = max(used[root], unused[root]);
	cout << ans.first << " " << fixed << setprecision(20) << ans.second/ans.first << "\n";
}