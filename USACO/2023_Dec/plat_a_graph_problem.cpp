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
	if(b==0)
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
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<ll> vals(n);
	vector<int> par(n);
	vector<vector<int>> sets(n);
	vector<ll> tenPows(n);
	tenPows[0] = 1;
	for(int i = 1; i < n; i++) {
		tenPows[i] = tenPows[i-1]*10%MOD;
	}
	for(int i = 0; i < n; i++) {
		par[i] = i;
		sets[i].push_back(i);
	}
	vector<pair<ll, ll>> funcs(n, {1, 0});
	
	function<void(int, int, ll)> merge = [&](int a, int b, ll edge) {

		ll aVal = vals[a];
		ll bVal = vals[b];

		a = par[a];
		b = par[b];
		auto aFunc = funcs[a];
		auto bFunc = funcs[b];
		aVal = (aVal*aFunc.first%MOD+aFunc.second)%MOD;
		bVal = (bVal*bFunc.first%MOD+bFunc.second)%MOD;
		
		if(a == b)
			return;
		if(sets[a].size() < sets[b].size()) {
			swap(a, b);
			swap(aVal, bVal);
			swap(aFunc, bFunc);
		}
		int aSz = (int)sets[a].size();
		int bSz = (int)sets[b].size();
		
		//update a function
		ll newFirst = aFunc.first*tenPows[bSz]%MOD;
		ll newSecond = aFunc.second*tenPows[bSz]%MOD;
		newSecond = (newSecond+edge*tenPows[bSz-1]%MOD)%MOD;
		newSecond = (newSecond+bVal)%MOD;
		funcs[a] = {newFirst, newSecond};
		
		//merge b into a
		for(int i : sets[b]) {
			par[i] = a;
			sets[a].push_back(i);
			vals[i] = (vals[i]*bFunc.first%MOD+bFunc.second)%MOD;
			vals[i] = vals[i]*tenPows[aSz]%MOD;
			vals[i] = (vals[i]+edge*tenPows[aSz-1]%MOD)%MOD;
			vals[i] = (vals[i]+aVal)%MOD;
			
			vals[i] = (vals[i]-funcs[a].second+MOD)%MOD;
			vals[i] = vals[i]*inv(funcs[a].first)%MOD;
		}
	};
	
	for(int e = 1; e <= m; e++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		merge(a, b, e);
	}
	for(int i = 0; i < n; i++) {
		auto func = funcs[par[i]];
		cout << (vals[i]*func.first%MOD+func.second)%MOD << "\n";
	}
}