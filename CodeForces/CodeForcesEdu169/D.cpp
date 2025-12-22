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

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<string> color(n);
		map<string, set<int>> seen;
		for(int i = 0; i < n; i++) {
			cin >> color[i];
			seen[color[i]].insert(i);
		}
		while(q-->0) {
			int x, y;
			cin >> x >> y;
			x--; y--;
			if(x > y)
				swap(x, y);
			string xc = color[x];
			string yc = color[y];
			bool intersect = false;
			for(char c : xc)
				if(yc[0] == c || yc[1] == c)
					intersect = true;
			if(intersect)
				cout << y-x << "\n";
			else {
				int best = INF;
				for(auto& [col, indices] : seen) {
					if(col == xc || col == yc)
						continue;
					auto it = indices.lower_bound(x);
					if(it != indices.end())
						best = min(best, abs(x-*it)+abs(y-*it));
					if(it != indices.begin()) {
						it = prev(it);
						best = min(best, abs(x-*it)+abs(y-*it));
					}
				}
				if(best == INF)
					cout << -1 << "\n";
				else
					cout << best << "\n";
			}
		}
	}
}