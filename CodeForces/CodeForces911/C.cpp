#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
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
		vector<char> moves(n);
		for(int i = 0; i < n; i++) {
			cin >> moves[i];
		}
		vector<int> left(n);
		vector<int> right(n);
		for(int i = 0; i < n; i++) {
			cin >> left[i] >> right[i];
			left[i]--; right[i]--;
		}
		
		int best = n;
		function<void(int, int)> dfs = [&](int curr, int cost) {
			if(left[curr] == -1 && right[curr] == -1) {
				best = min(best, cost);
				return;
			}
			if(left[curr] != -1) {
				dfs(left[curr], cost + (moves[curr] == 'L' ? 0 : 1));
			}
			if(right[curr] != -1) {
				dfs(right[curr], cost + (moves[curr] == 'R' ? 0 : 1));
			}
		};
		
		dfs(0, 0);
		
		cout << best << "\n";
	}
}