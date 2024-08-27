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
		vector<vector<int>> aCon(n);
		vector<vector<int>> bCon(n);
		for(int i = 1; i < n; i++) {
			int p;
			cin >> p;
			p--;
			aCon[p].push_back(i);
		}
		for(int i = 1; i < n; i++) {
			int p;
			cin >> p;
			p--;
			bCon[p].push_back(i);
		}
		vector<int> tin(n);
		vector<int> tout(n);
		int time = 0;
		function<void(int)> dfsB = [&](int curr) {
			tin[curr] = time++;
			for(int next : bCon[curr])
				dfsB(next);
			tout[curr] = time++;
		};
		dfsB(0);
		set<pair<int, int>> group;
		int ans = 0;
		function<void(int)> dfsA = [&](int curr) {
			ans = max(ans, sz(group));
			for(int next : aCon[curr]) {
				int start = tin[next];
				int end = tout[next];
				auto it = group.upper_bound({start, end});
				//i contain someone
				if(it != group.end() && it->first < end) {
					dfsA(next);
				}
				else {
					bool remove = false;
					pair<int, int> val;
					//someone else contains me
					if(it != group.begin()) {
						it--;
						if(it->second > start) {
							val = *it;
							remove = true;
						}
					}
					if(remove)
						group.erase(val);
					group.insert({start, end});
					dfsA(next);
					group.erase({start, end});
					if(remove)
						group.insert(val);
				}
			}
		};
		group.insert({tin[0], tout[0]});
		dfsA(0);
		cout << ans << "\n";
	}
}