#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <bit>


using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	vector<int> toggle(20);
	for(int i = 1; i <= 20; i++) {
		for(int j = i; j <= 20; j+=i) {
			toggle[i-1] |= (1<<(j-1));
		}
	}
	vector<vector<int>> pos(20);
	for(int i = 1; i <= 20; i++) {
		for(int subset = 1; subset < (1<<i); subset++) {
			int on = 0;
			for(int bit = 0; bit < i; bit++) {
				if(subset&(1<<bit))
					on ^= toggle[bit]&((1<<i)-1);
			}
			if(popcount((unsigned int)on) > i/5)
				continue;
			pos[i-1].push_back(subset);
		}
	}
	
	
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> needed(n);
		for(int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			if(n <= 20)
				needed[u] |= (1<<v);
		}
		if(n > 20) {
			cout << n << "\n";
			for(int i = 1; i <= n; i++) 
				cout << i << " ";
			cout << "\n";
		}
		else {
			int ans = -1;
			for(int subset: pos[n-1]) {
				bool bad = false;
				for(int bit = 0; bit < n; bit++) {
					if((subset&(1<<bit)) && ((subset&needed[bit])!=needed[bit])) {
						bad = true;
						break;
					}
				}
				if(bad)
					continue;
				
				ans = subset;
				break;
			}
			if(ans == -1)
				cout << -1 << "\n";
			else {
				cout << popcount((unsigned int)ans) << "\n";
				for(int i = 0; i < n; i++) {
					if(ans&(1<<i))
						cout << i+1 << " ";
				}
				cout << "\n";
			}
		}
	}
}