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
		int n, d;
		cin >> n >> d;
		vector<int> prio(n);
		vector<int> period(n);
		for(int i = 0; i < n; i++) {
			cin >> prio[i] >> period[i];
		}
		vector<int> suffPrio(n+1);
		for(int i = n-1; i >= 0; i--) {
			suffPrio[i] = max(suffPrio[i+1], prio[i]);
		}
		
		auto blocker = [&](int myPrio) {
			int left = 0, right = n;
			while(left <= right) {
				int mid = (left+right)/2;
				if(suffPrio[mid] < myPrio) {
					right = mid-1;
				}
				else {
					left = mid+1;
				}
			}
			return right;
		};
		
		vector<bool> fed(n);
		int amtFed = 0;
		int ans = -1;
		int currIndex = 0;
		int counter = 0;
		
		priority_queue<pair<pair<int, int>, int>> front;
		vector<priority_queue<pair<pair<int, int>, int>>> queues(n);
		for(int i = 0; i < n; i++)
			queues[i].push({{prio[i], counter}, i});
			
		priority_queue<pair<pair<int, int>, int>> waiting;
		
		auto feed = [&](int id, int time) {
			if(!fed[id]) {
				amtFed++;
				fed[id] = true;
				if(amtFed == n)
					return true;
			}
			waiting.push({{-(time+period[id]), -period[id]}, id});
			return false;
		};
		
		for(int round = 1; round <= d; round++) {
			//feed front person
			if(!front.empty()) {
				auto next = front.top().second;
				front.pop();
				if(feed(next, round)) {
					ans = round;
					break;
				}
			}
			else {
				//feed next person
				if(currIndex < n) {
					auto next = queues[currIndex].top().second;
					queues[currIndex].pop();
					if(feed(next, round)) {
						ans = round;
						break;
					}
				}
				//else noone fed
			}
			
			while(currIndex < n && queues[currIndex].empty())
					currIndex++;
			
			while(!waiting.empty() && -waiting.top().first.first == round) {
				int me = waiting.top().second;
				waiting.pop();
				int reenterSpot = blocker(prio[me]);
				if(reenterSpot < currIndex || currIndex == n)
					front.push({{prio[me], -(counter++)}, me});
				else
					queues[reenterSpot].push({{prio[me], -(counter++)}, me});
			}
			
		}
		cout << ans << "\n";
	}
}