#include <iostream>
#include <vector>
#include <algorithm>

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
		pair<int, int> lines[n];
		vector<pair<int, int>> sorted_lines;
		for(int i = 0; i < n; i++) {
			int l, r;
			cin >> l >> r;
			lines[i] = {l, r};
			sorted_lines.push_back({r-l, i});
		}
		sorted_lines.push_back({(int)1e6, n});
		sort(sorted_lines.begin(), sorted_lines.end());
		vector<int> contains[n+1];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(i == j)
					continue;
				if(lines[j].first >= lines[i].first && lines[j].second <= lines[i].second) {
					contains[i].push_back(j);
				}
			}
		}
		for(int i = 0; i < n; i++) {
			contains[n].push_back(i);
		}
		vector<int> best(n+1);
		for(auto line : sorted_lines) {
			int id = line.second;

			vector<pair<int, int>> events;
			for(auto inner : contains[id]) {
				int r = lines[inner].second;
				events.push_back({r, inner});
			}
			sort(events.begin(), events.end());

			vector<int> dp(events.size()+1);
			for(int i = 0; i < (int)events.size(); i++) {
				int left = 0, right = i;
				int curr_id = events[i].second;
				int l = lines[curr_id].first;
				while(left < right) {
					int mid = (left+right)/2;
					if(events[mid].first < l) {
						left = mid+1;
					}
					else {
						right = mid;
					}
				}
				dp[i+1] = max(dp[i], best[curr_id]+dp[left]);
			}

			best[id] = dp.back()+1;

			
		}

		cout << best[n]-1 << "\n";
	}
}