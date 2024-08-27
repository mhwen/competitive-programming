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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> p(n+1);
		vector<int> sizes(n+1, 1);
		iota(p.begin(), p.end(), 0);
		int components = n;
		function<int(int)> getPar = [&](int a) {
			if(p[a] == a)
				return a;
			return p[a] = getPar(p[a]);
		};
		
		auto merge = [&](int a, int b) {
			a = getPar(a);
			b = getPar(b);
			if(a == b)
				return false;
			if(sizes[a] < sizes[b])
				swap(a, b);
			p[b] = a;
			components--;
			return true;
		};
		
		vector<ll> costs(n+1);
		
		//-n = add
		//n = delete
		vector<pair<int, int>> events;
		for(int i = 1; i <= n; i++) {
			int l, r;
			cin >> l >> r >> costs[i];
			events.push_back({l, -i});
			events.push_back({r, i});
		}
		
		sort(events.begin(), events.end());
		set<pair<ll, int>> seen;
		vector<pair<ll, pair<int, int>>> merges;
		for(auto [_, op] : events) {
			if(op < 0) {
				op = abs(op);
				seen.insert({costs[op], op});
			}
			else {
				seen.erase({costs[op], op});
				auto it = seen.lower_bound({costs[op], 0});
				if(it != seen.end()) {
					int above = it->second;
					merges.push_back({costs[above]-costs[op], {op, above}});
				}
				it = seen.lower_bound({costs[op]+1, 0});
				if(it != seen.begin()) {
					it--;
					int below = it->second;
					merges.push_back({costs[op]-costs[below], {op, below}});
				}
			}
		}
		ll ans = 0;
		sort(merges.begin(), merges.end());
		for(auto [cost, info] : merges) {
			if(merge(info.first, info.second))
				ans += cost;
		}
		if(components == 1)
			cout << ans << "\n";
		else
			cout << -1 << "\n";
	}
}