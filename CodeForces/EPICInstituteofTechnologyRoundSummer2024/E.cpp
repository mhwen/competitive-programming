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

constexpr ll INF = 1e13;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> vals(n);
		for(int i = 0; i < n; i++)
			cin >> vals[i];
		vector<vector<int>> con(n);
		for(int i = 1; i < n; i++) {
			int p;
			cin >> p;
			p--;
			con[p].push_back(i);
		}
		vector<vector<ll>> available(n, vector<ll>(n+1));
		
		ll ans = 0;
		
		function<void(int)> dfs = [&](int curr) {
			ll childSums = 0;
			if(con[curr].empty())
				available[curr][0] = INF;
			else {
				for(int next : con[curr]) {
					dfs(next);
					childSums += vals[next];
					for(int slack = 0; slack < n; slack++) {
						available[curr][slack+1] += available[next][slack];
					}
				}
				available[curr][0] = max(0LL, childSums-vals[curr]);
				for(int slack = 0; slack < n; slack++) {
					ll take = min(max(0LL, vals[curr]-childSums), available[curr][slack]);
					childSums += take;
					available[curr][slack] -= take;
					ans += slack*take;
				}
			}
		};
		
		dfs(0);
		
		cout << ans << "\n";
	}
}