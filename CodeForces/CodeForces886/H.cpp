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
constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<pair<int, ll>>> con(n);
		for(int i = 0; i < m; i++) {
			int a, b, d;
			cin >> a >> b >> d;
			a--; b--;
			con[a].push_back({b, d});
			con[b].push_back({a, -d});
		}
		vector<ll> loc(n, INF);
		function<bool(int, ll)> dfs = [&](int curr, ll location) {
			if(loc[curr] != INF) {
				if(loc[curr] != location)
					return false;
				else
					return true;
			}
			loc[curr] = location;
			bool res = true;
			for(auto next : con[curr]) {
				res &= dfs(next.first, location+next.second);
			}
			return res;
		};
		bool good = true;
		for(int i = 0; i < n; i++) {
			if(loc[i] == INF) {
				if(!dfs(i, 0)) {
					good = false;
					break;
				}
			}
		}
		if(good)	
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}