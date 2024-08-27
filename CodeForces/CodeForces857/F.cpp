#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

bool compare(pair<ll, ll> a, pair<ll, ll> b) {
	if(b.first == -1)
		return true;
	if(a.first > b.first)
		return false;
	else if(a.first == b.first)
		return a.second > b.second;
	else
		return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		ll p;
		cin >> n >> m >> p;
		vector<pair<ll, int>> sorted_profit(n);
		vector<vector<pair<int, ll>>> con(n);
		for(int i = 0; i < n; i++) {
			ll w;
			cin >> w;
			sorted_profit[i] = {w, i};
		}
		sort(sorted_profit.begin(), sorted_profit.end());
		for(int i = 0; i < m; i++) {
			int a, b;
			ll s;
			cin >> a >> b >> s;
			a--;
			b--;
			con[a].push_back({b, s});
		}
		vector<pair<ll, ll>> best(n);
		best[0] = {0, p};
		for(int i = 1; i < n; i++) {
			best[i] = {-1, -1};
		}
		
		int start = 0;
		while(sorted_profit[start].second != 0)
			start++;
		for(int i = start; i < n; i++) {
			int curr_id = sorted_profit[i].second;
			if(best[curr_id].first == -1)
				continue;
			ll weight = sorted_profit[i].first;
			ll steps = best[curr_id].first;
			ll extra = best[curr_id].second;
			priority_queue<pair<ll, int>> queue;
			vector<ll> cost(n, -1);
			queue.push({0, curr_id});
			while(!queue.empty()) {
				pair<ll, int> curr = queue.top();
				queue.pop();
				ll dist = -curr.first;
				int id = curr.second;
				if(cost[id] != -1)
					continue;
				cost[id] = dist;
				for(pair<int, ll> next : con[curr.second]) {
					if(cost[next.first] == -1)
						queue.push({-dist-next.second, next.first});
				}
			}

			for(int j = 0; j < n; j++) {
				if(cost[j] != -1) {
					ll needed = max(0LL, cost[j]-extra);
					ll steps_needed = (needed+weight-1)/weight;
					ll new_extra = steps_needed*weight+extra-cost[j];
					pair<ll, ll> candidate_best = {steps_needed+steps, new_extra};
					if(compare(candidate_best, best[j])) {
						best[j] = candidate_best;
					}
				}
			}
		}

		cout << best[n-1].first << "\n";
	}
}