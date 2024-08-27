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
		for(int i = 1; i < n; i++) {
			int p;
			cin >> p;
			p--;
			con[p].push_back(i);
		}
		
		vector<int> sizes(n);
		function<void(int)> dfs = [&](int curr) {
			sizes[curr] = 1;
			for(int next : con[curr]) {
				dfs(next);
				sizes[curr] += sizes[next];
			}
		};
		dfs(0);
		
		int teams = 0;
		function<void(int, int)> solve = [&](int curr, int used) {
			int largest = 0;
			int id = -1;
			for(int next : con[curr]) {
				if(sizes[next] > largest) {
					largest = sizes[next];
					id = next;
				}
			}
			int total = sizes[curr]-1;
			used = max(0, used-1);
			if(largest-used <= total-largest) {
				teams += (total-used)/2;
			}
			else {
				teams += total-largest;
				solve(id, total-largest+used);
			}
		};
		solve(0, 0);
		cout << teams << "\n";
	}
}