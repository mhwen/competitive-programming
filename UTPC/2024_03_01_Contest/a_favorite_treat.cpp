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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> costs(n);
	for(int i = 0; i < n; i++) {
		cin >> costs[i];
	}
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		con[u].push_back(v);
		con[v].push_back(u);
	}
	vector<ll> seen(1<<n, -1);
	seen[0] = 0;
	function<ll(int)> search = [&](int mask) {
		if(seen[mask] != -1)
			return seen[mask];
		ll best = 0;
		vector<int> candidates;
		for(int i = 0; i < n; i++) {
			if((mask & (1<<i)) == 0)
				continue;
			int count = 0;
			for(int next : con[i]) {
				if(mask & (1<<next))
					count++;
			}
			if(count == 1)
				candidates.push_back(i);
		}
		
		for(int ii = 0; ii < (int)candidates.size(); ii++) {
			for(int jj = ii+1; jj < (int)candidates.size(); jj++) {
				int i = candidates[ii];
				int j = candidates[jj];
				mask -= (1<<i);
				mask -= (1<<j);
				best = max(best, min(costs[i], costs[j])+search(mask));
				mask += (1<<i);
				mask += (1<<j);
			}
		}
		return seen[mask] = best;
	};
	
	cout << search((1<<n)-1) << "\n";
}