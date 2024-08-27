#include <iostream>
#include <vector>
#include <set>
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
		vector<vector<int>> tracks(n);
		set<int> coords;
		for(int i = 0; i < n; i++) {
			int k;
			cin >> k;
			for(int j = 0; j < k; j++) {
				int a;
				cin >> a;
				tracks[i].push_back(a);
				coords.insert(a);
			}
		}
		map<int, int> ids;
		int index = 1;
		for(int i : coords) {
			ids[i] = index++;
		}
		
		vector<int> dp(ids.size()+2);
		vector<vector<pair<int, int>>> events(ids.size()+2);
		for(int i = 0; i < n; i++) {
			vector<int> sequence;
			for(int a : tracks[i]) {
				int id = ids[a];
				if(sequence.empty() || id > sequence.back())
					sequence.push_back(id);
			}
			for(int j = (int)sequence.size()-1; j >= 0; j--) {
				events[sequence[j]].push_back({sequence.back(), (int)sequence.size()-j});
			}
		}
		for(int i = 1; i < (int)dp.size(); i++) {
			dp[i] = max(dp[i], dp[i-1]);
			for(pair<int, int> interval : events[i]) {
				int next = interval.first;
				int weight = interval.second;
				dp[next] = max(dp[next], dp[i-1]+weight);
			}
		}
		cout << dp[(int)ids.size()+1] << "\n";
	}
}