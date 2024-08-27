#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int>>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		a--;
		b--;
		con[a].push_back({w, b});
	}
	vector<vector<pair<int, int>>> incoming(n);
	for(int i = 0; i < n; i++) {
		sort(con[i].begin(), con[i].end());
		int sz = (int)con[i].size();
		for(int j = 0; j < sz; j++) {
			incoming[con[i][j].second].push_back({sz, j+1});
		}
	}
	vector<vector<vector<vector<bool>>>> bad(10, vector<vector<vector<bool>>>(10, vector<vector<bool>>(10, vector<bool>(10))));
	for(int i = 0; i < n; i++) {
		set<pair<int, int>> seen;
		sort(incoming[i].begin(), incoming[i].end());
		for(auto next : incoming[i]) {
			if(seen.count(next))
				bad[next.first][next.second][next.first][next.second] = true;
			else
				seen.insert(next);
		}
		incoming[i].resize(unique(incoming[i].begin(), incoming[i].end()) - incoming[i].begin());
		for(int j = 0; j < (int)incoming[i].size(); j++) {
			for(int h = j+1; h < (int)incoming[i].size(); h++) {
				auto left = incoming[i][j];
				auto right = incoming[i][h];
				bad[left.first][left.second][right.first][right.second] = true;
			}
		}
	}
	
	
	int ans = 0;
	vector<int> perm(k+1);
	function<void(int)> check = [&](int curr) {
		if(curr == k+1) {
			for(int left = 1; left <= k; left++) {
				for(int right = left; right <= k; right++) {
					if(bad[left][perm[left]][right][perm[right]])
						return;
				}
			}
			ans++;
			return;
		}
		for(int i = 1; i <= curr; i++) {
			perm[curr] = i;
			check(curr+1);
		}
	};
	
	check(1);
	
	cout << ans << "\n";
	
}