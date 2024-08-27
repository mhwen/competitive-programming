#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> ans(n);
	vector<pair<int, int>> actions(n);
	vector<set<int>> seen(n+1);
	bool pos = true;
	for(int i = 0; i < n; i++) {
		int t, x;
		cin >> t >> x;
		actions[i] = {t, x};
		if(t == 1)
			seen[x].insert(i);
		else {
			if(seen[x].empty())
				pos = false;
			else {
				int found = *seen[x].rbegin();
				ans[found] = 1;
				seen[x].erase(found);
			}
		}
	}

	if(!pos)
		cout << -1 << "\n";
	else {
		int hold = 0;
		int greatest = 0;
		for(int i = 0; i < n; i++) {
			if(actions[i].first == 1) {
				hold += ans[i];
			}
			else {
				hold--;
			}
			greatest = max(greatest, hold);
		}
		cout << greatest << "\n";
		for(int i = 0; i < n; i++) {
			if(actions[i].first == 1)
				cout << ans[i] << " ";
		}
		cout << "\n";
	}
	
}