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
		vector<int> p(n);
		vector<int> dep(n);
		function<void(int, int, int)> dfs = [&](int curr, int prev, int d) {
			dep[curr] = d;
			p[curr] = prev;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, d+1);
			}
		};
		dfs(0, -1, 0);
		
		auto query = [](int x) {
			cout << "? " << x+1 << endl;
			int res;
			cin >> res;
			return res;
		};
		
		vector<bool> alive(n, true);
		
		auto check = [&]() {
			int cnt = 0;
			int ans = -1;
			for(int i = 0; i < n; i++) {
				if(alive[i]) {
					cnt++;
					ans = i;
				}
			}
			if(cnt == 0)
				return 0;
			if(cnt == 1)
				return ans;
			return -1;
		};
		
		auto isLeaf = [&](int curr) {
			int cnt = 0;
			for(int child : con[curr]) {
				if(alive[child] && child != p[curr])
					cnt++;
			}
			return cnt == 0;
		};
		
		auto getSubtree = [&](int root) {
			vector<bool> inSubtree(n);
			function<void(int, int)> go = [&](int curr, int prev) {
				inSubtree[curr] = true;
				for(int next : con[curr]) {
					if(next == prev || !alive[next])
						continue;
					go(next, curr);
				}
			};
			go(root, p[root]);
			return inSubtree;
		};
				
		int root = 0;
		
		int times = 0;
		while(true) {
			times++;
			if(times > 160)
				return -1;
			int bot = root;
			for(int i = 0; i < n; i++) {
				if(alive[i] && dep[i] > dep[bot])
					bot = i;
			}
			int half = (dep[bot]-dep[root])/2;
			for(int i = 0; i < half; i++) {
				bot = p[bot];
			}
			
			vector<bool> inSubtree = getSubtree(bot);
			
			if(query(bot)) {
				//kill everything outside subtree
				for(int i = 0; i < n; i++)
					if(!inSubtree[i])
						alive[i] = false;
				root = bot;
			}
			else {
				//kill subtree and every leaf
				for(int i = 0; i < n; i++)
					if(inSubtree[i])
						alive[i] = false;
				vector<int> leaves;
				for(int i = 0; i < n; i++)
					if(alive[i] && isLeaf(i))
						leaves.push_back(i);
				for(auto l : leaves)
					alive[l] = false;
					
				if(root != 0) {
					root = p[root];
					alive[root] = true;
				}
			}
			
			int res = check();
			if(res != -1) {
				cout << "! " << res+1 << endl;
				break;
			}
		}
	}
}