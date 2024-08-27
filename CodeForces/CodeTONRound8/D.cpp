#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<vector<ll>> costs(n+1, vector<ll>(n+1));
		for(int i = 1; i <= n; i++) {
			for(int j = i; j <= n; j++) {
				cin >> costs[i][j];
			}
		}
		vector<vector<ll>> dpTake(n+1);
		vector<vector<ll>> dpLeave(n+1);
		dpLeave[0].push_back(0);
		for(int i = 1; i <= n; i++) {
			priority_queue<pair<ll, pair<int, int>>> q;
			for(int j = i-1; j >= 0; j--) {
				q.push({dpLeave[j].front()+costs[j+1][i], {j, 0}});
			}
			while(!q.empty() && (int)dpTake[i].size() < k) {
				auto next = q.top();
				q.pop();
				dpTake[i].push_back(next.first);
				int id = next.second.first;
				int take = next.second.second;
				take++;
				if(take < (int)dpLeave[id].size())
					q.push({dpLeave[id][take]+costs[id+1][i], {id, take}});
			}
			int prevLeave = 0, prevTake = 0;
			int leaveSz = (int)dpLeave[i-1].size();
			int takeSz = (int)dpTake[i-1].size();
			while((int)dpLeave[i].size() < k && (prevLeave < leaveSz || prevTake < takeSz)) {
				if(prevLeave == leaveSz) {
					dpLeave[i].push_back(dpTake[i-1][prevTake++]);
				}
				else if(prevTake == takeSz) {
					dpLeave[i].push_back(dpLeave[i-1][prevLeave++]);
				}
				else {
					if(dpTake[i-1][prevTake] > dpLeave[i-1][prevLeave]) {
						dpLeave[i].push_back(dpTake[i-1][prevTake++]);
					}
					else {
						dpLeave[i].push_back(dpLeave[i-1][prevLeave++]);
					}
				}
			}
		}
		vector<ll> ans;
		for(ll l : dpTake[n])
			ans.push_back(l);
		for(ll l : dpLeave[n])
			ans.push_back(l);
		sort(ans.rbegin(), ans.rend());
		for(int i = 0; i < k; i++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
	}
}