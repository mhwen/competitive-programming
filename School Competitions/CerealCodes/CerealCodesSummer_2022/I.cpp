#include <iostream>
#include <vector>
#include <queue>

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
		vector<ll> weights(n);
		vector<ll> strengths(n);
		for(int i = 0; i < n; i++) {
			cin >> weights[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> strengths[i];
		}
		int count = 0;
		bool pos = true;
		for(int i = 0; i < n; i++) {
			priority_queue<pair<ll, int>> queue;
			ll weightSum = 0;
			for(int j = i; j < n; j++) {
				weightSum += weights[j];
				queue.push({strengths[j-i]-weightSum, j-i});
			}
			ll removed = 0;
			int index = 0;
			while(!queue.empty()) {
				int bestIndex = -1;
				ll newRemoved = 0;
				while(!queue.empty() && queue.top().first+removed >= 0) {
					int id = queue.top().second;
					if(id > bestIndex) {
						bestIndex = id;
						newRemoved = -queue.top().first+strengths[id];
					}
					queue.pop();
				}
				if(bestIndex == -1) {
					pos = false;
					break;
				}
				removed = newRemoved;
				index = bestIndex;
				count++;
				while(!queue.empty() && queue.top().second < index) {
					queue.pop();
				}
			}
			if(!pos) {
				count = -1;
				break;
			}
		}
		cout << count << "\n";
	}
}