#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;
constexpr ll DEPTH = 61;

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res=res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;

	vector<ll> sizes(DEPTH);
	sizes[0] = 1;
	for(int i = 1; i < DEPTH; i++) {
		sizes[i] = 2*sizes[i-1]+1;
	}
	vector<vector<ll>> paths(DEPTH, vector<ll>(DEPTH*2));
	vector<vector<ll>> rootPaths(DEPTH, vector<ll>(DEPTH*2));
	rootPaths[0][1] = paths[0][1] = 1;
	for(int i = 1; i < DEPTH; i++) {
		rootPaths[i][1] = 1;
		paths[i][1] = (2*paths[i-1][1]+1)%MOD;
		for(int a = 2; a < DEPTH*2; a++) {
			paths[i][a] = 2*(paths[i-1][a]+rootPaths[i-1][a-1])%MOD;
			rootPaths[i][a] = 2*rootPaths[i-1][a-1]%MOD;
		}
		
		for(int a = 1; a < DEPTH*2; a++) {
			for(int b = 1; b < DEPTH*2; b++) {
				if(a+b+1 >= DEPTH*2)
					continue;
				paths[i][a+b+1] += rootPaths[i-1][a]*rootPaths[i-1][b]%MOD;
				paths[i][a+b+1] %= MOD;
			}
		}
	}
	
	vector<ll> pathCount(DEPTH*2);
	
	function<vector<ll>(ll)> findPaths = [&] (ll sz) {
		if(sz == 0)
			return vector<ll>(DEPTH*2);
		for(int i = 0; i < DEPTH; i++) {
			if(sz == sizes[i]) {
				for(int j = 0; j < 2*DEPTH; j++) {
					pathCount[j] += paths[i][j];
					pathCount[j] %= MOD;
				}
			}
		}
		vector<ll> left;
		vector<ll> right;
		if(sz == 2) {
			left = findPaths(1);
			right = findPaths(0);
		}
		else {
			for(int i = 0; i < DEPTH; i++) {
				ll rem = sz-1-sizes[i];
				if((i == 0 || sizes[i-1] <= rem) && rem <= sizes[i+1]) {
					left = findPaths(sizes[i]);
					right = findPaths(rem);
					break;
				}
			}
		}

		vector<ll> myRootPaths(2*DEPTH);
		myRootPaths[1] = 1;
		pathCount[1]++;
		pathCount[1] %= MOD;
		for(int a = 2; a < DEPTH*2; a++) {
			pathCount[a] += left[a-1]+right[a-1];
			pathCount[a] %= MOD;
			myRootPaths[a] = (left[a-1]+right[a-1])%MOD;
		}
		
		for(int a = 1; a < DEPTH*2; a++) {
			for(int b = 1; b < DEPTH*2; b++) {
				if(a+b+1 >= DEPTH*2)
					continue;
				pathCount[a+b+1] += left[a]*right[b]%MOD;
				pathCount[a+b+1] %= MOD;
			}
		}
		
		return myRootPaths;
		
	};
	
	
	
	
	while(t-->0) {
		ll n, m;
		cin >> n >> m;
		fill(pathCount.begin(), pathCount.end(), 0);
		auto g = findPaths(n);
		// for(auto ii : pathCount)
			// cout << ii << " ";
		// cout << endl << endl;
		
		ll counts = 0;
		for(int i = 1; i < 2*DEPTH; i++) {
			ll otherWays = pow(m, n-i);
			for(int j = 1; j <= m; j++) {

				ll ways = (pow(j, i)-pow(j-1, i)+MOD)%MOD;
				ll add = pathCount[i]*ways%MOD*otherWays%MOD*j%MOD;
				counts += add;
				counts %= MOD;
			}
		}
		
		cout << counts << "\n";
		
	}
	
	
}