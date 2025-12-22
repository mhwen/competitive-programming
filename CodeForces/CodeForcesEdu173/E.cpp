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


bool solve(vector<vector<int>>& a, vector<vector<int>>& b) {
	int n = sz(a);
	int m = sz(a[0]);
	vector<vector<int>> con(n+m);
	vector<int> start;
	
	auto row = [&](int r) {
		return r;
	};
	auto col = [&](int c) {
		return c+n;
	};
	
	// rows 1->0
	for(int r = 0; r < n; r++) {
		bool bad = false;
		for(int c = 0; c < m; c++) {
			if(b[r][c] == 1)
				con[row(r)].push_back(col(c));
			if(a[r][c] == 1 && b[r][c] == 0)
				bad = true;
		}
		if(bad)
			start.push_back(row(r));
	}
	// cols 0->1
	for(int c = 0; c < m; c++) {
		bool bad = false;
		for(int r = 0; r < n; r++) {
			if(b[r][c] == 0)
				con[col(c)].push_back(row(r));
			if(a[r][c] == 0 && b[r][c] == 1)
				bad = true;
		}
		if(bad)
			start.push_back(col(c));
	}
	vector<int> vis(n+m);
	
	auto dfs = [&](int curr, auto&& self) -> bool {
		vis[curr] = 1;
		for(int next : con[curr]) {
			if(vis[next] == 1)
				return true;
			if(vis[next] == 0 && self(next, self))
				return true;
		}
		vis[curr] = 2;
		return false;
	};
	
	for(auto s : start)
		if(dfs(s, dfs))
			return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector a(n, vector<ll>(m));
		vector b(n, vector<ll>(m));
		for(int r = 0; r < n; r++)
			for(int c = 0; c < m; c++)
				cin >> a[r][c];
		for(int r= 0; r < n; r++)
			for(int c = 0; c < m; c++)
				cin >> b[r][c];
				
		auto getBit = [&](ll bit, vector<vector<ll>>& x) {
			vector res(n, vector<int>(m));
			for(int r = 0; r < n; r++) {
				for(int c = 0; c < m; c++) {
					if((x[r][c]&bit) == 0)
						res[r][c] = 0;
					else
						res[r][c] = 1;
				}
			}
			return res;
		};
		
		bool good = true;
		
		for(ll bit = 0; bit < 30; bit++) {
			auto A = getBit(1<<bit, a);
			auto B = getBit(1<<bit, b);
			good &= solve(A, B);
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}