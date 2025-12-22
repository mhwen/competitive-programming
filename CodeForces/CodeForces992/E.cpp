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
		int n, q;
		cin >> n >> q;
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<int> p(n);
		function<void(int, int)> dfs = [&](int curr, int prev) {
			p[curr] = prev;
			for(int next : con[curr])
				if(next != prev)
					dfs(next, curr);
		};
		dfs(0,0);
		while(q-->0) {
			int v, P;
			cin >> v >> P;
			v--;
			vector<int> comps;
			int cnt = 0;
			while(v != 0) {
				if(cnt%2==1)
					comps.push_back(sz(con[v]));
				cnt++;
				v = p[v];
			}
			int ans = cnt;
			sort(all(comps));
			for(int i = 0; i < sz(comps)-P; i++)
				ans = ans+2*comps[i]-2;
			cout << ans << "\n";
		}
	}
}