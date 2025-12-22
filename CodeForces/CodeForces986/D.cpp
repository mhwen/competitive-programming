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

char c[3] = {'q', 'k', 'j'};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<pair<char, int>>> con(n);
		vector<vector<int>> ranks(3, vector<int>(n));
		vector<set<pair<int, int>>> avail(3);
		vector<vector<bool>> vis(3, vector<bool>(n));
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				cin >> ranks[i][j];
				avail[i].insert({ranks[i][j], j});
			}
		}

		vector<pair<char, int>> prev(n, {'x', -1});
		
		for(int curr = 0; curr < n; curr++) {
			if(curr != 0 && prev[curr].second == -1)
				continue;
			for(int j = 0; j < 3; j++) {
				while(!avail[j].empty()) {
					auto it = avail[j].lower_bound({ranks[j][curr], curr});
					if(it == avail[j].begin())
						break;
					it--;
					int next = it->second;
					if(next < curr)
						avail[j].erase(*it);
					else if(!vis[j][next]) {
						prev[next] = {c[j], curr};
						avail[j].erase(*it);
						vis[j][next] = true;
					}
					else
						break;
				}
			}
		}
		
		if(prev[n-1].second == -1)
			cout << "NO\n";
		else {
			cout << "YES\n";
			vector<pair<char, int>> moves;
			int curr = n-1;
			while(curr != 0) {
				moves.push_back({prev[curr].first, curr});
				curr = prev[curr].second;
			}
			reverse(all(moves));
			cout << sz(moves) << "\n";
			for(auto [C, i] : moves)
				cout << C << " " << i+1 << "\n";
		}
	}
}