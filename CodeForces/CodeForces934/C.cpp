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
			int u, v;
			cin >> u >> v;
			u--; v--;
			con[u].push_back(v);
			con[v].push_back(u);
		}
		
		int furthest = 0;
		int start = 0;
		
		function<void(int, int, int)> dfs = [&](int curr, int prev, int dist) -> void {
			if(dist > furthest) {
				furthest = dist;
				start = curr;
			}
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, dist+1);
			}
		};
		
		dfs(start, -1, 0);
		int end = start;
		furthest = 0;
		dfs(start, -1, 0);
		
		stack<int> currPath;
		stack<int> path;
		
		function<void(int, int)> dfs2 = [&](int curr, int prev) -> void {
			currPath.push(curr);
			if(curr == end) {
				path = currPath;
			}
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs2(next, curr);
			}
			currPath.pop();
		};
		
		dfs2(start, -1);
		
		
		furthest++;
		if(furthest%2==1) {
			for(int i = 0; i < furthest/2; i++) {
				path.pop();
			}
			int focus = path.top()+1;
			cout << (furthest+1)/2 << "\n";
			for(int i = 0; i < (furthest+1)/2; i++) {
				cout << focus << " " << i << "\n";
			}
		}
		else {
			for(int i = 0; i < furthest/2-1; i++) {
				path.pop();
			}
			int a = path.top()+1;
			path.pop();
			int b = path.top()+1;
			cout << (furthest+2)/4*2 << "\n";
			int dist = furthest/2-1;
			for(int i = 1; i <= (furthest+2)/4; i++) {
				cout << a << " " << dist << "\n";
				cout << b << " " << dist << "\n";
				dist-=2;
			}
		}
		
		
	}
}