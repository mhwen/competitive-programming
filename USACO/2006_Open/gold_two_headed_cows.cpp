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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	
	vector<vector<pair<int, bool>>> con(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		char ha, hb;
		cin >> a >> ha >> b >> hb;
		a--; b--;
		bool diff = ha == hb;
		if(a < b)
			swap(a, b);
		con[a].push_back({b, diff});
	}
	
	vector<map<int, int>> types(n);
	for(int i = 0; i < n; i++)
		types[i][i] = 0;
	vector<int> par(n);
	iota(all(par), 0);
	
	function<int(int)> getPar = [&](int a) {
		if(a == par[a])
			return a;
		return par[a] = getPar(par[a]);
	};
	
	auto merge = [&](int a, int b, bool diff) {
		int aPar = getPar(a);
		int bPar = getPar(b);
		bool flip = (types[aPar][a]!=types[bPar][b])^diff;
		if(aPar == bPar)
			return !flip;
		a = aPar;
		b = bPar;
		if(sz(types[a]) < sz(types[b]))
			swap(a, b);
		for(auto [id,type] : types[b]) {
			types[a][id] = type^flip;
		}
		par[b] = a;
		return true;
	};
	
	auto reset = [&](int a) {
		par[a] = a;
		types[a].clear();
		types[a][a] = 0;
	};
	
	int curr = 0;
	int ans = 1;
	for(int i = 0; i < n; i++) {
		for(auto [id,diff] : con[i]) {
			if(id < curr)
				continue;
			if(!merge(i, id, diff)) {
				ans++;
				curr = i;
				reset(i);
				break;
			}
		}
	}
	cout << ans << "\n";
}