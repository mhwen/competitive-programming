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
		int n;
		cin >> n;
		vector<pair<ll, int>> intervals;
		vector<ll> left(n);
		vector<ll> right(n);
		vector<ll> costs(n);
		for(int i = 0; i < n; i++) {
			cin >> left[i];
			intervals.push_back({left[i], 0});
		}
		for(int i = 0; i < n; i++) {
			cin >> right[i];
			intervals.push_back({right[i], 1});
		}
		for(int i = 0; i < n; i++) {
			cin >> costs[i];
		}
		sort(intervals.begin(), intervals.end());
		priority_queue<ll> amnts;
		stack<ll> s;
		for(int i = 0; i < (int)intervals.size(); i++) {
			auto next = intervals[i];
			if(next.second == 0)
				s.push(next.first);
			else {
				ll p = s.top();
				s.pop();
				amnts.push(next.first-p);
			}
		}
		sort(costs.begin(), costs.end());
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ll next = amnts.top();
			amnts.pop();
			ans += costs[i]*next;
		}
		cout << ans << "\n";
		
	}
}