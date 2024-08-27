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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> reqs(n);
		for(int i = 0; i < n; i++) {
			cin >> reqs[i];
		}
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<vector<pair<ll, ll>>> costs(n, vector<pair<ll, ll>>(20));
		vector<ll> sizes(n);
		function<ll(int, int)> process = [&](int curr, int prev) {
			ll size = 1;
			for(int next : con[curr]) {
				if(next == prev)
					continue;	
								
				size += process(next, curr);
				
				for(int bit = 0; bit < 20; bit++) {
					costs[curr][bit].first += costs[next][bit].first;
					costs[curr][bit].second += costs[next][bit].second;
				}
			}
			for(int bit = 0; bit < 20; bit++) {
				if(reqs[curr] & (1<<bit)) {
					costs[curr][bit].first = costs[curr][bit].second+size*(1<<bit);
				}
				else {
					costs[curr][bit].second = costs[curr][bit].first+size*(1<<bit);
				}
			}
			return sizes[curr] = size;
		};
		process(0, -1);
		
		vector<ll> ans(n);
		function<void(int, int, vector<pair<ll, ll>>)> solve = [&](int curr, int prev, vector<pair<ll, ll>> prevCosts) {
			vector<pair<ll, ll>> myCosts(20);
			for(int next : con[curr]) {
				if(next == prev)
					continue;
				
				for(int bit = 0; bit < 20; bit++) {
					myCosts[bit].first += costs[next][bit].first;
					myCosts[bit].second += costs[next][bit].second;
				}
			}
			for(int bit = 0; bit < 20; bit++) {
				myCosts[bit].first += prevCosts[bit].first;
				myCosts[bit].second += prevCosts[bit].second;
				if(reqs[curr] & (1<<bit)) {
					ans[curr] += myCosts[bit].second;
				}
				else {
					ans[curr] += myCosts[bit].first;
				}
			}
			
			for(int next : con[curr]) {
				if(next == prev)
					continue;
					
				vector<pair<ll, ll>> nextCosts(20);
				for(int bit = 0; bit < 20; bit++) {
					ll flipCost = (n-sizes[next])*(1<<bit);
					if(reqs[curr] & (1<<bit)) {
						nextCosts[bit].first = myCosts[bit].second-costs[next][bit].second+flipCost;
						nextCosts[bit].second = myCosts[bit].second-costs[next][bit].second;
					}
					else {
						nextCosts[bit].first = myCosts[bit].first-costs[next][bit].first;
						nextCosts[bit].second = myCosts[bit].first-costs[next][bit].first+flipCost;
					}
				}
				solve(next, curr, nextCosts);
			}
		};
		
		solve(0, -1, vector<pair<ll, ll>>(20));
		for(ll i : ans)
			cout << i << " ";
		cout << "\n";
	}
}