#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	multiset<int> sizes;
	vector<int> ratings(n);
	vector<pair<int, int>> events;
	for(int i = 0; i < n; i++) {
		cin >> ratings[i];
		events.emplace_back(ratings[i], i);
	}
	string status;
	cin >> status;
	sort(events.begin(), events.end());
	
	
	vector<int> score(n);
	vector<int> p(n);
	iota(p.begin(), p.end(), 0);
	function<int(int)> getPar = [&](int a) {
		if(a == p[a])
			return a;
		return p[a] = getPar(p[a]);
	};
	auto merge = [&](int a, int b) {
		a = getPar(a);
		b = getPar(b);
		if(a == b)
			return;
		if(score[a] < score[b])
			swap(a, b);
		sizes.erase(sizes.find(score[a]));
		sizes.erase(sizes.find(score[b]));
		p[b] = a;
		score[a] += score[b];
		sizes.insert(score[a]);
	};
	auto subtract = [&](int a) {
		a = getPar(a);
		sizes.erase(sizes.find(score[a]));
		score[a]--;
		sizes.insert(score[a]);
	};
	
	set<int> alive;
	for(int i = 0; i < n; i++) {
		alive.insert(i);
		if(status[i] == '1') {
			score[i] = 1;
			sizes.insert(1);
		}
	}
	for(int i = 0; i < n-1; i++) {
		if(status[i] == '1' && status[i+1] == '1')
			merge(i, i+1);
	}
	
	int ans = 0;
	if(!sizes.empty() && *sizes.rbegin() >= k)
		ans = events[0].first;
	
	for(int i = 0; i < sz(events); i++) {
		int id = events[i].second;
		if(status[id] == '0') {
			//check if merge possible
			alive.erase(id);
			auto it = alive.upper_bound(id);
			if(it != alive.end() && it != alive.begin()) {
				int above = *it;
				int below = *prev(it);
				if(status[above] == '1' && status[below] == '1')
					merge(above, below);
			}
		}
		else {
			//subtract from score of component
			alive.erase(id);
			subtract(id);
		}
		
		//processed all with this rating
		if(i < sz(events)-1 && events[i].first != events[i+1].first) {
			if(!sizes.empty() && *sizes.rbegin() >= k)
				ans = events[i+1].first;
		}
	}
	cout << ans << "\n";
}