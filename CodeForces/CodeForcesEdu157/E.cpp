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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> myAtt(n);
		vector<int> myDef(n);
		vector<pair<int, int>> mySorted(n);
		for(int i = 0; i < n; i++) {
			cin >> myAtt[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> myDef[i];
		}
		for(int i = 0; i < n; i++) {
			mySorted[i] = {myAtt[i], myDef[i]};
		}
		sort(mySorted.begin(), mySorted.end());
		for(int i = n-2; i >= 0; i--) {
			mySorted[i].second = max(mySorted[i].second, mySorted[i+1].second);
		}	
		
		int m;
		cin >> m;
		vector<int> theirAtt(m);
		vector<int> theirDef(m);
		vector<pair<int, int>> theirSorted(m);
		for(int i = 0; i < m; i++) {
			cin >> theirAtt[i];
		}
		for(int i = 0; i < m; i++) {
			cin >> theirDef[i];
		}
		for(int i = 0; i < m; i++) {
			theirSorted[i] = {theirAtt[i], theirDef[i]};
		}
		sort(theirSorted.begin(), theirSorted.end());
		for(int i = m-2; i >= 0; i--) {
			theirSorted[i].second = max(theirSorted[i].second, theirSorted[i+1].second);
		}
		
		map<pair<int, int>, int> vis;
		//0 = in progress
		//1 = i win
		//2 = i lose
		
		function<int(pair<int, int>)> dfs = [&](pair<int, int> info) {
			int curr = info.first;
			int side = info.second;
			if(vis.count(info))
				return vis[info];
			
			vis[info] = 0;
			
			if(side) {
				auto it = upper_bound(theirSorted.begin(), theirSorted.end(), make_pair(curr, (int)1e9));
				if(it == theirSorted.end()) {
					vis[info] = 1;
				}
				else {
					vis[info] = dfs({it->second, side^1});
				}
			}
			else {
				auto it = upper_bound(mySorted.begin(), mySorted.end(), make_pair(curr, (int)1e9));
				if(it == mySorted.end()) {
					vis[info] = 2;
				}
				else {
					vis[info] = dfs({it->second, side^1});
				}
			}
			return vis[info];
		};
		
		vector<int> ans(3);
		for(int i = 0; i < n; i++) {
			ans[dfs({myDef[i], 1})]++;
		}
		
		cout << ans[1] << " " << ans[0] << " " << ans[2] << "\n";
	}
}