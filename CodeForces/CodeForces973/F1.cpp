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
		vector<int> par(n);
		int u, v;
		cin >> u >> v;
		u--; v--;
		vector<bool> onPath(n);
		onPath[u] = true;
		vector<int> path;
		vector<int> len(n, 1);
		vector<int> dp(n, 1);
		function<void(int, int)> dfs = [&](int curr, int prev) {
			par[curr] = prev;
			int best = 0;
			int bestLen = 0;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
				bestLen = max(bestLen, len[next]);
				if(onPath[next])
					onPath[curr] = true;
				else
					best = max(best, len[next]);
			}
			len[curr] += bestLen;
			dp[curr] += best;
			if(onPath[curr])
				path.push_back(curr);
		};
		dfs(0, 0);
		reverse(all(path));
		
		vector<int> alice(sz(path));
		vector<int> bob(sz(path));
		multiset<int> A;
		multiset<int> B;
		for(int i = 0; i < sz(path)-1; i++) {
			alice[i] = dp[path[i]]+i;
			A.insert(alice[i]);
		}
		for(int i = sz(path)-1; i > 0; i--) {
			bob[i] = dp[path[i]]+sz(path)-1-i;
			B.insert(bob[i]);
		}
		int ai = 0;
		int bi = sz(path)-1;
		string winner = sz(path)%2 ? "Alice" : "Bob";
		int move = 0;
		while(ai < bi) {
			//Alice
			if(move%2==0) {
				if(alice[ai] > *B.rbegin()) {
					winner = "Alice";
					break;
				}
				else {
					A.erase(A.find(alice[ai]));
					ai++;
					B.erase(B.find(bob[ai]));
				}
			}
			//Bob
			else {
				if(bob[bi] >= *A.rbegin()) {
					winner = "Bob";
					break;
				}
				else {
					B.erase(B.find(bob[bi]));
					bi--;
					A.erase(A.find(alice[bi]));
				}
			}
			move++;
		}
		cout << winner << "\n";
		
	}
}