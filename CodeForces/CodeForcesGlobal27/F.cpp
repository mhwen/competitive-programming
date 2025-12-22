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

constexpr ll INF = 2e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, root;
		cin >> n >> root;
		root--;
		vector<ll> vals(n);
		for(int i = 0; i < n; i++) {
			cin >> vals[i];
		}
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		
		auto run = [&](ll ops) {
			auto dfs = [&](auto&& self, int curr, int prev) -> ll {
				ll myOps = ops/n;
				if(curr < ops%n)
					myOps++;
				ll over = 0;
				for(int next : con[curr]) {
					if(next == prev)
						continue;
					ll need = self(self, next, curr);
					if(need <= myOps) {
						myOps -= need;
					}
					else {
						over += need-myOps;
						myOps = 0;
					}
				}
				ll need = vals[curr];
				if(need <= myOps) {
					myOps -= need;
				}
				else {
					over += need-myOps;
					myOps = 0;
				}
				if(myOps == 0)
					return over;
				else
					return myOps%2;
			};
			
			if(dfs(dfs, root, -1) == 0)
				return ops;
			return INF;
		};
		
		ll tot = accumulate(all(vals), 0LL);
		
		auto check = [&](ll val) {
			ll best = INF;
			for(int i = 0; i < 2*n; i++) {
				if((val+i)%2 != tot%2)
					continue;
				best = min(best, run(val+i));
				if(best != INF)
					return best;
			}
			return best;
		};
		
		ll l = tot;
		ll r = tot*n;
		ll best = INF;
		while(l <= r) {
			ll mid = l+(r-l)/2;
			auto res = check(mid);
			if(res != INF) {
				best = min(best, res);
				r = mid-1;
			}
			else
				l = mid+1;
		}
		cout << best << "\n";
	}
}