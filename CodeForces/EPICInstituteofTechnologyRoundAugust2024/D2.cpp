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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<vector<int>> con(n+1);
		vector<int> par(n+1);
		for(int i = 2; i <= n; i++) {
			cin >> par[i];
			con[par[i]].push_back(i);
		}
		con[0].push_back(1);
		vector<int> idAtIndex(n+1);
		vector<int> indexOfId(n+1);
		for(int i = 1; i <= n; i++) {
			cin >> idAtIndex[i];
			indexOfId[idAtIndex[i]] = i;
		}
		vector<int> sizes(n+1);
		vector<set<pair<int, int>>> children(n+1);
		function<void(int)> dfs = [&](int curr) {
			sizes[curr] = 1;
			for(int next : con[curr]) {
				dfs(next);
				sizes[curr] += sizes[next];
				children[curr].insert({indexOfId[next], next});
			}
		};
		dfs(0);
		
		
		auto check = [&](int id) {
			set<int> bad;
			if(!children[id].empty()) {
				int myIndex = indexOfId[id];
				auto lowest = *children[id].begin();
				auto highest = *children[id].rbegin();
				if(lowest.first <= myIndex || highest.first+sizes[highest.second]-1 > myIndex+sizes[id]-1)
					bad.insert(id);
			}
			return bad;
		};
		
		int bad = 0;
		for(int i = 0; i <= n; i++) {
			if(!check(i).empty())
				bad++;
		}
		
		auto getBads = [&](int id) {
			auto parentBad = check(par[id]);
			auto meBad = check(id);
			parentBad.insert(all(meBad));
			return parentBad;
		};
		
		auto getBothBads = [&](int x, int y) {
			auto xBads = getBads(x);
			auto yBads = getBads(y);
			xBads.insert(all(yBads));
			return sz(xBads);
		};
		
		auto doSwap = [&](int x, int y) {
			int oldXIndex = indexOfId[x];
			int oldYIndex = indexOfId[y];
			children[par[x]].erase(children[par[x]].find({oldXIndex, x}));
			children[par[y]].erase(children[par[y]].find({oldYIndex, y}));
			
			int newXIndex = oldYIndex;
			int newYIndex = oldXIndex;
			
			idAtIndex[newXIndex] = x;
			idAtIndex[newYIndex] = y;
			indexOfId[x] = newXIndex;
			indexOfId[y] = newYIndex;
			children[par[x]].insert({newXIndex, x});
			children[par[y]].insert({newYIndex, y});
			
		};
		
		while(q-->0) {
			int x, y;
			cin >> x >> y;
			x = idAtIndex[x];
			y = idAtIndex[y];
			bad -= getBothBads(x, y);
			doSwap(x, y);
			bad += getBothBads(x, y);
			cout << (bad ? "NO" : "YES") << "\n";
		}
	}
}