#include <iostream>
#include <vector>
#include <functional>
#include <map>

using namespace std;

typedef long long ll;

int main() {
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
		vector<bool> symmetrical(n);
		map<vector<int>, int> idMap;
		vector<int> ids(n);
		int id = 1;
		function<int(int, int)> dfs = [&](int curr, int prev) {
			vector<int> children;
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				children.push_back(dfs(next, curr));
			}
			sort(children.begin(), children.end());

			int currId = id;
			if(idMap.find(children) != idMap.end()) {
				currId = idMap[children];
			}
			else {
				idMap[children] = id;
				
				bool good = true;
				int c = 0;
				int count = 0;
				int odds = 0;
				for(int i : children) {
					if(i != c) {
						if(count%2==1) {
							odds++;
							good &= symmetrical[c];
						}
						count = 1;
						c = i;
					}
					else {
						count++;
					}
				}
				if(count%2==1) {
					odds++;
					good &= symmetrical[c];
				}
				if(odds > 1)
					good = false;
				symmetrical[currId] = good;			
				id++;
			}
			
			return ids[curr] = currId;
		};
		
		dfs(0, -1);
		cout << (symmetrical[ids[0]] ? "YES" : "NO") << "\n";
	}
}