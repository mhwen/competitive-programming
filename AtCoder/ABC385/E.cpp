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
	int n;
	cin >> n;
	vector<int> deg(n);
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		con[u].push_back(v);
		con[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	int ans = n-3;
	for(int curr = 0; curr < n; curr++) {
		vector<int> d;
		for(int next : con[curr])
			d.push_back(deg[next]-1);
		sort(all(d));
		reverse(all(d));
		for(int i = 0; i < sz(d); i++) {
			if(d[i] == 0)
				break;
			int rem = d[i]*(i+1);
			int keep = 1+i+1+rem;
			ans = min(ans, n-keep);
		}
	}
	cout << ans << "\n";
}