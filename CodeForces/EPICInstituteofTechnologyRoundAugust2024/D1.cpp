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
		vector<int> par(n+1);
		par[0] = -1;
		for(int i = 2; i <= n; i++) {
			cin >> par[i];
		}
		vector<int> pos(n+1);
		pos[0] = -1;
		for(int i = 1; i <= n; i++) {
			cin >> pos[i];
		}
		
		vector<int> mapping(n+1);
		vector<int> realOrder(n+1);
		
		int id = 0;
		function<void(int)> dfs = [&](int curr) {
			id++;
			mapping[id] = curr;
			realOrder[curr] = pos[id];
			if(curr*2+1 > n)
				return;
			int c1 = curr*2;
			int c2 = curr*2+1;
			dfs(c1);
			dfs(c2);
		};
		
		dfs(1);

		auto getBad = [&](int a) {
			set<pair<int, int>> bads;
			int aGuy = realOrder[a];
			if(a > 1) {
				int aPar = realOrder[a/2];
				if(par[aGuy] != aPar)
					bads.insert({aPar, aGuy});
			}
			if(a*2+1 <= n) {
				int c1 = a*2;
				int c2 = a*2+1;
				int child1 = realOrder[c1];
				int child2 = realOrder[c2];
				if(par[child1] != aGuy)
					bads.insert({aGuy, child1});
				if(par[child2] != aGuy)
					bads.insert({aGuy, child2});
			}
			return bads;
		};
		
		auto countBad = [&](vector<int>& query) {
			set<pair<int, int>> bads;
			for(int i : query) {
				auto badI = getBad(i);
				bads.insert(all(badI));
			}
			return sz(bads);
		};
		
		vector<int> allIs(n);
		iota(all(allIs), 1);
		
		int bad = countBad(allIs);

		while(q-->0) {
			int a, b;
			cin >> a >> b;
			a = mapping[a];
			b = mapping[b];
			vector<int> query{a, b};
			bad -= countBad(query);
			swap(realOrder[a], realOrder[b]);
			bad += countBad(query);
			if(bad == 0)
				cout << "YES\n";
			else 
				cout << "NO\n";
		}
	}
}