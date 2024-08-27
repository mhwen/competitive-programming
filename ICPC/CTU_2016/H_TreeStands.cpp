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

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	while(cin >> n >> k) {
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<vector<ll>> noGuy(n, vector<ll>(k+1));
		vector<vector<ll>> need(n, vector<ll>(k+1));
		vector<vector<ll>> dontNeed(n, vector<ll>(k+1));
		function<void(int, int)> dfs = [&](int curr, int prev) {
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
			}
			vector<ll> myNoGuy(k+1);
			myNoGuy[0] = 1;
			vector<ll> myNeed(k+1);
			myNeed[1] = 1;
			vector<ll> myDontNeed(k+1);
			
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				for(int finalSize = k; finalSize >= 0; finalSize--) {
					ll mng = 0, mdn = 0, mn = 0;
					for(int theirSize = 0; theirSize <= finalSize; theirSize++) {
						int mySize = finalSize-theirSize;
						ll theirWays = (noGuy[next][theirSize]+dontNeed[next][theirSize])%MOD;
						mng += myNoGuy[mySize]*theirWays%MOD;
						mng %= MOD;
						
						mn += myNeed[mySize]*noGuy[next][theirSize]%MOD;
						mn %= MOD;
						
						theirWays = (need[next][theirSize] + dontNeed[next][theirSize])%MOD;
						ll fromNeed = myNeed[mySize]*theirWays%MOD;
						theirWays = (need[next][theirSize] + dontNeed[next][theirSize] + noGuy[next][theirSize])%MOD;
						ll fromDontNeed = myDontNeed[mySize]*theirWays%MOD;
						mdn += (fromNeed+fromDontNeed)%MOD;
						mdn %= MOD;
					}
					myNoGuy[finalSize] = mng;
					myNeed[finalSize] = mn;
					myDontNeed[finalSize] = mdn;
				}
			}
			noGuy[curr] = myNoGuy;
			need[curr] = myNeed;
			dontNeed[curr] = myDontNeed;
		};
		
		dfs(0, -1);
		cout << (noGuy[0][k]+dontNeed[0][k])%MOD << "\n";
	}
}