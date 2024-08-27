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

int id(int val) {
	int res = (abs(val)-1)*2;
	if(val < 0)
		return res^1;
	else
		return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> info(3, vector<int>(n));
		for(int r = 0; r < 3; r++) {
			for(int c = 0; c < n; c++) {
				cin >> info[r][c];
			}
		}
		vector<vector<int>> con(2*n);
		vector<vector<int>> rev_con(2*n);
		for(int C = 0; C < n; C++) {
			int a = id(info[0][C]);
			int b = id(info[1][C]);
			int c = id(info[2][C]);
			con[a^1].push_back(b);
			con[a^1].push_back(c);
			con[b^1].push_back(a);
			con[b^1].push_back(c);
			con[c^1].push_back(a);
			con[c^1].push_back(b);
			
			rev_con[b].push_back(a^1);
			rev_con[c].push_back(a^1);
			rev_con[a].push_back(b^1);
			rev_con[c].push_back(b^1);
			rev_con[a].push_back(c^1);
			rev_con[b].push_back(c^1);
		}
		
		vector<int> order;
		vector<bool> vis(2*n);
		
		function<void(int)> dfs1 = [&](int curr) {
			vis[curr] = true;
			for(int next : con[curr])
				if(!vis[next])
					dfs1(next);
			order.push_back(curr);
		};
		
		vector<int> component(2*n, -1);
		
		function<void(int, int)> dfs2 = [&](int curr, int comp) {
			component[curr] = comp;
			for(int next : rev_con[curr])
				if(component[next] == -1)
					dfs2(next, comp);
		};

		for(int i = 0; i < 2*n; i++) {
			if(!vis[i])
				dfs1(i);
		}
		
		reverse(order.begin(), order.end());
		int id = 0;
		fill(vis.begin(), vis.end(), false);
		for(int i : order) {
			if(component[i] == -1) {
				dfs2(i, id++);
			}
		}
		
		bool good = true;
		for(int i = 0; i < 2*n; i+=2) {
			if(component[i] == component[i+1])
				good = false;
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}