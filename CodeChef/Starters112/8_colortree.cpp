#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 1e9+7;

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

int main() {
	
	vector<ll> fact(4e5);
	vector<ll> invFact(4e5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < (int)fact.size(); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = pow(fact[i], MOD-2);
	}
	
	function<ll(ll, ll)> choose = [&](ll a, ll b) {
		// cout << a << " " << b << endl;
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
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
		vector<int> sizes(n);
		vector<ll> ways(n);
		
		function<void(int, int)> dfs = [&](int curr, int prev) {
			sizes[curr] = 1;
			ways[curr] = 1;
			ll total = 0;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr);
				if(sizes[next]%2==1)
					total++;
				ways[curr] = ways[curr]*ways[next]%MOD;
				sizes[curr] += sizes[next];
			}
			ll chooseWays = choose(total, total/2);
			if(total%2==0 && total > 0)
				chooseWays = (chooseWays+choose(total, total/2-1))%MOD;
			ways[curr] = ways[curr]*chooseWays%MOD;
			if(sizes[curr]%2==0)
				ways[curr] = ways[curr]*2%MOD;
		};
		
		dfs(0, -1);
		if(n%2==1)
			ways[0] = ways[0]*2%MOD;
		cout << ways[0] << "\n";
		
		// cout << "k\n";
		// for(int i = 0; i < n; i++)
			// cout << i+1 << " " << ways[i] << endl;
	}
}