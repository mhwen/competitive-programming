#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> adj(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a] |= 1<<b;
		adj[b] |= 1<<a;
	}
	vector<int> dp(1<<n);
	for(int i = 0; i < n; i++) {
		dp[1<<i] = 1<<i;
	}
	bool found = false;
	for(int i = 1; i < 1<<n; i++) {
		int graph = 0;
		for(int j = 0; j < n; j++) {
			if(i&(1<<j)) {
				graph |= adj[j];
			}
		}
		int low = __builtin_ctz(i);
		if(graph==(1<<n)-1 && (adj[low] & dp[i])) {
			vector<int> cycle;
			int g = i;
			int curr = low;
			while(g != 0) {
				int next = __builtin_ctz(adj[curr] & dp[g]);
				cycle.push_back(next);
				g ^= 1<<next;
				curr = next;
			}
			vector<int> p(n, -1);
			for(int j = 0; j < (int)cycle.size(); j++) {
				p[cycle[j]] = cycle[(j+1)%cycle.size()];
			}
			for(int j = 0; j < n; j++) {
				if(p[j] == -1) {
					p[j] = __builtin_ctz(adj[j]&i);
				}
			}
			cout << "Yes\n";
			for(int i = 0; i < n; i++) {
				cout << p[i]+1 << " ";
			}
			cout << "\n";
			found = true;
			break;
		}
		
		
		int mask = 0;
		for(int j = 0; j < n; j++) {
			if(dp[i]&(1<<j)) {
				mask |= adj[j];
			}
		}
		for(int j = low; j < n; j++) {
			if((~i&(1<<j)) && (mask&(1<<j))) {
				dp[i|(1<<j)] |= 1<<j;
			}
		}
	}
	
	if(!found)
		cout << "No\n";
}