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
		vector<int> dep(n);
		vector<int> maxDep(n);
		function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
			dep[curr] = d;
			maxDep[curr] = d;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, d+1);
				maxDep[curr] = max(maxDep[curr], maxDep[next]);
			}
		};
		dfs(0, 0, 0);
		vector<ll> p(n+2);
		for(int i = 0; i < n; i++) {
			p[dep[i]]++;
			p[maxDep[i]+1]--;
		}
		ll best = 0;
		for(int i = 0; i < sz(p); i++) {
			if(i > 0)
				p[i] += p[i-1];
			best = max(best, p[i]);
		}
		cout << n-best << "\n";
	}
}