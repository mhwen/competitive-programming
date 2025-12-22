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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll w;
		cin >> n >> w;
		vector<int> p(n);
		for(int i = 1; i < n; i++) {
			cin >> p[i];
			p[i]--;
		}
		vector<ll> weights(n, -1);
		ll score = w*n;
		int freeLeft = n;
		
		vector<int> parent(n);
		iota(all(parent), 0);
		vector<set<int>> comps(n);
		for(int i = 0; i < n; i++)
			comps[i].insert(i);
		
		ll sum = 0;
			
		auto removePath = [&](int a, int b) {
			score -= w-sum;
			freeLeft--;
		};
		
		function<int(int)> getPar = [&](int a) {
			if(a == parent[a])
				return a;
			return parent[a] = getPar(parent[a]);
		};
		
		auto merge = [&](int a, int b) {
			a = getPar(a);
			b = getPar(b);
			if(a == b)
				return;
			if(sz(comps[a]) < sz(comps[b]))
				swap(a, b);
			for(auto guy : comps[b]) {
				if(comps[a].count((guy-1+n)%n))
					removePath((guy-1+n)%n, guy);
				if(comps[a].count((guy+1)%n))
					removePath(guy, (guy+1)%n);
			}
			for(auto guy : comps[b])
				comps[a].insert(guy);
			parent[b] = a;
		};
		
		for(int i = 0; i < n-1; i++) {
			int child;
			ll y;
			cin >> child >> y;
			child--;
			int par = p[child];
			score -= (freeLeft-2)*y;
			sum += y;
			weights[child] = y;
			merge(par, child);
			cout << score << " ";
		}
		cout << "\n";
	}
}