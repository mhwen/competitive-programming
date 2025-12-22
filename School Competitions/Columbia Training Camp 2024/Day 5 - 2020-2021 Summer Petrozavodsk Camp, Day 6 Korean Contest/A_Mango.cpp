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
#include <cassert>

using namespace std;
typedef __int128 ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

//https://codeforces.com/group/ejaj3Dzoql/contest/544965

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string m, s;
	cin >> m >> s;
	int k, q;
	cin >> k >> q;
	
	vector<string> components;
	string prev = "";
	int xs = 0;
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == '$') {
			xs++;
			if(sz(prev))
				components.push_back(prev);
			components.push_back("$");
			prev = "";
		}
		else {
			prev += s[i];
		}
	}
	if(sz(prev))
		components.push_back(prev);
	vector<ll> levelSizes{sz(m)};
	
	if(xs > 1) {
		int extras = sz(s)-xs;
		while(k > 0 && levelSizes.back() <= (ll)1e18) {
			levelSizes.push_back(extras+xs*levelSizes.back());
			k--;
		}
	}
	vector<vector<ll>> levelComps(1);
	for(int i = 1; i < sz(levelSizes); i++) {
		vector<ll> lc{0};
		for(auto& c : components) {
			if(c == "$")
				lc.push_back(lc.back()+levelSizes[i-1]);
			else
				lc.push_back(lc.back()+sz(c));
		}
		levelComps.push_back(lc);
	}
	
	
	ll numPrefixes = max(0, k);
	string prefix = s.substr(0, s.find("$"));
	ll prefixLen = numPrefixes*sz(prefix);
	auto solvePrefix = [&](ll l, ll r) {
		ll curr = l;
		while(curr < prefixLen && curr <= r) {
			cout << prefix[(long long)(curr%sz(prefix))];
			curr++;
		}
	};
	string suffix = s.substr(s.find_last_of("$")+1);
	auto solveSuffix = [&](ll curr, ll l, ll r) {
		ll index = max((ll)0, l-curr);
		curr = max(curr, l);
		while(curr <= r) {
			cout << suffix[(long long)(index%sz(suffix))];
			index++;
			curr++;
		}
	};
	function<void(int, ll, ll, ll)> solve = [&](int level, ll curr, ll l, ll r) {
		if(curr > r)
			return;
		//reached base string
		if(level == 0) {
			ll index = max((ll)0, l-curr);
			curr = max(curr, l);
			while(index < (ll)sz(m) && curr <= r) {
				cout << m[(long long)index];
				index++;
				curr++;
			}
		}
		else {
			auto start = upper_bound(all(levelComps[level]), max((ll)0, l-curr));
			start--;
			int i = (int)(start-levelComps[level].begin());
			curr += levelComps[level][i];
			while(i < sz(levelComps[level])-1 && curr <= r) {
				if(components[i] == "$") {
					solve(level-1, curr, l , r);
					curr += levelSizes[level-1];
				}
				else {
					ll index = max((ll)0, l-curr);
					curr = max(curr, l);
					while(index < (ll)sz(components[i]) && curr <= r) {
						cout << components[i][(long long)index];
						index++;
						curr++;
					}
				}
				i++;
			}
		}
	};
		
	while(q-->0) {
		long long a, b;
		cin >> a >> b;
		a--; b--;
		solvePrefix(a, b);
		solve(sz(levelSizes)-1, prefixLen, a, b);
		solveSuffix(prefixLen+levelSizes.back(), a, b);
		cout << "\n";
	}
	
}