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
	ll x;
	int k;
	cin >> x >> k;
	priority_queue<pair<ll, int>> next;
	vector<queue<pair<ll, ll>>> queues(k);
	for(int i = 0; i < k; i++) {
		ll curr = 0;
		ll cost = 0;
		int l;
		cin >> l;
		while(l-->0) {
			ll val;
			cin >> val;
			curr += val;
			cost = min(cost, curr);
			if(curr > 0) {
				queues[i].push({cost, curr});
				curr = 0;
				cost = 0;
			}
		}
	}
	for(int i = 0; i < k; i++) {
		if(!queues[i].empty())
			next.push({queues[i].front().first, i});
	}
	while(!next.empty()) {
		auto take = next.top();
		next.pop();
		if(x+take.first >= 0) {
			x += queues[take.second].front().second;
			queues[take.second].pop();
			if(!queues[take.second].empty()) {
				next.push({queues[take.second].front().first, take.second});
			}
		}
	}
	cout << x << "\n";
}