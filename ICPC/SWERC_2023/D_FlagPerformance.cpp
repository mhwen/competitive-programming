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
constexpr ll MOD = 1000000007LL;
// constexpr ll MOD = 999999937LL;
ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	#define int ll
	vector<ll> fact(100);
	vector<ll> invFact(100);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < (int)fact.size(); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	function<ll(int, int)> choose = [&](int a, int b) {
		return fact[a]*invFact[b]%MOD*invFact[a-b]%MOD;
	};
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, t;
	cin >> n >> k >> t;
	vector<map<vector<int>, ll>> states(k+1);
	vector<int> start(n+1);
	start[1] = n;
	states[0][start] = 1;
	for(int i = 0; i < k; i++) {
		// cout << i << endl;
		// ll totCount = 0;
		for(auto ss : states[i]) {
			vector<int> state = ss.first;
			ll stateCount = ss.second;
			// // totCount += stateCount;
			// cout << "count: " << stateCount << " | ";
			// for(int j : state)
				// cout << j << " ";
			// cout << endl;

			//merge
			for(int a = 1; a <= n; a++) {
				if(state[a] == 0)
					continue;
				for(int b = a; b <= n; b++) {
					if(state[b] == 0)
						continue;
					ll numWays = a*b;
					if(a == b) {
						if(state[a] == 1)
							continue;
						ll choice = (state[a]*(state[a]-1)/2)%MOD;
						numWays = numWays*choice%MOD;
					}
					else {
						ll choice = state[a]*state[b]%MOD;
						numWays = numWays*choice%MOD;
					}
					numWays = numWays*stateCount%MOD;
					if(numWays > 0) {
						vector<int> newState = state;
						newState[a]--;
						newState[b]--;
						newState[a+b]++;
						states[i+1][newState] += numWays;
						states[i+1][newState] %= MOD;
					}
				}
			}
			//split
			for(int a = 2; a <= n; a++) {
				if(state[a] == 0)
					continue;
				for(int pile1 = 1; pile1 <= a-1; pile1++) {
					int pile2 = a-pile1;
					if(pile1 > pile2)
						break;
					ll numWays;
					if(pile1==pile2) {
						numWays = a/2;
					}
					else {
						numWays = a;
					}
					numWays = numWays*state[a]%MOD*stateCount%MOD;
					if(numWays > 0) {
						vector<int> newState = state;
						newState[a]--;
						newState[pile1]++;
						newState[pile2]++;
						states[i+1][newState] += numWays;
						states[i+1][newState] %= MOD;
					}
				}
			}
			
		}
		// cout << totCount << endl;
	}
	// cout << k << endl;
	// for(auto ss : states[k]) {
		// vector<int> state = ss.first;
		// ll stateCount = ss.second;
		// cout << "count: " << stateCount << " | ";
		// for(int j : state)
			// cout << j << " ";
		// cout << endl;
	// }
	while(t-->0) {
		vector<int> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			nums[i]--;
		}
		vector<bool> vis(n);
		vector<int> counts(n+1);
		for(int i = 0; i < n; i++) {
			if(!vis[i]) {
				int curr = i;
				int sz = 0;
				while(!vis[curr]) {
					sz++;
					vis[curr] = true;
					curr = nums[curr];
				}
				counts[sz]++;
			}
		}
		
		ll divideBy = 1;
		int rem = n;
		for(int sz = 1; sz <= n; sz++) {
			if(counts[sz] == 0)
				continue;
			// cout << sz << " count " << counts[sz] << endl;
			int freq = counts[sz];
			int tot = sz*freq;
			ll chooseGroup = choose(rem, tot);
			ll chooseWithinGroup = fact[tot]*
									inv(pow(sz, freq))%MOD*
									inv(fact[freq])%MOD;
			// cout << chooseGroup << " " << chooseWithinGroup << endl;
			rem -= tot;
			divideBy = divideBy*chooseGroup%MOD*chooseWithinGroup%MOD;
		}
		
		cout << states[k][counts]*inv(divideBy)%MOD << "\n";
	}
	
	
}