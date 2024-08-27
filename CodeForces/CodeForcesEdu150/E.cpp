#include <iostream>
#include <vector>
#include <algorithm>
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
		vector<pair<int, int>> columns;
		for(int i = 1; i <= n; i++) {
			int a;
			cin >> a;
			columns.push_back({n-a, i});
		}
		ll m;
		cin >> m;
		sort(columns.begin(), columns.end());
		map<int, int> intervals;
		vector<pair<ll, ll>> rects;
		intervals[0] = 0;
		intervals[n+1] = 0;
		for(auto& [height, index] : columns) {
			auto it = intervals.upper_bound(index);
			auto right = *it;
			auto left = *(--it);
			int prev = left.second;
			ll width = right.first-left.first-1;
			if(width > 0)
				rects.push_back({width, height-prev});
			intervals[left.first] = height;
			intervals[index] = height;
		}
		sort(rects.begin(), rects.end());
		reverse(rects.begin(), rects.end());
		int index = 0;
		ll used = 0;
		ll ans = m;
		while(m > 0) {
			ll width = rects[index].first;
			ll count = rects[index].second;
			if(m >= width*count) {
				m -= width*count;
				used += count;
			}
			else {
				used += (m+width-1)/width;
				m = 0;
			}
			index++;
		}
		cout << ans-used << "\n";
	}
}