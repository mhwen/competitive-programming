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
		ll x1;
		cin >> n >> x1;
		//we know all top right points must pair with downward facing cows
		//and all bottom right points must pair with upward facing cows
		//the left-side points can pair with either type of cow;
		//we will divide those up to fulfill the amount of each type of cow as needed
		vector<pair<ll, ll>> top;
		vector<pair<ll, ll>> bot;
		vector<pair<ll, ll>> free;
		for(int i = 0; i < n; i++) {
			ll y1, y2, x2;
			cin >> y1 >> y2 >> x2;
			top.push_back({y2, x2});
			bot.push_back({y1, x2});
			free.push_back({y2, x1});
			free.push_back({y1, x1});
		}
		sort(free.begin(), free.end());
		vector<ll> downCows;
		vector<ll> upCows;
		for(int i = 0; i < 4*n; i++) {
			ll s;
			cin >> s;
			if(s < 0)
				downCows.push_back(-s);
			else
				upCows.push_back(s);
		}
		//if we don't have enough downward facing cows to pair with the top right corners,
		//or not enough upward facing cows to pair with bottom right corners,
		//we know the answer is not possible
		if(downCows.size() < top.size() || upCows.size() < bot.size()) {
			cout << -1 << "\n";
			continue;
		}
		sort(downCows.begin(), downCows.end());
		sort(upCows.begin(), upCows.end());
		//give the lowest left-side points to the downward cows
		//and the highest left-side points to the upward ones
		while(bot.size() < upCows.size()) {
			bot.push_back(free.back());
			free.pop_back();
		}
		while(top.size() < downCows.size()) {
			top.push_back(free.back());
			free.pop_back();
		}
		
		//to check if an upper limit for the downward cows is possible,
		//we want to see if we can assign downward cows to points such that
		//none of them have to be placed higher than this limit.
		//we can reformulate it as: for each point, there is a maximum slope
		//that the cow assigned to this point can have without exceeding the limit
		//we can calculate these maximum slopes for each point, then sort them
		//and greedily assign cows to them in sorted order
		//if this process fails, then we know it is not possible in general
		//otherwise, it is possible
		auto checkTop = [&](ll limit) -> bool {
			vector<ll> maxes;
			for(auto point : top) {
				ll y = point.first;
				ll x = point.second;
				if(y >= limit)
					return false;
				maxes.push_back((limit-y)/x);
			}
			sort(maxes.begin(), maxes.end());
			for(int i = 0; i < (int)downCows.size(); i++) {
				if(downCows[i] > maxes[i])
					return false;
			}
			return true;
		};
		
		auto checkBot = [&](ll limit) -> bool {
			vector<ll> mins;
			for(auto point : bot) {
				ll y = point.first;
				ll x = point.second;
				if(y <= limit)
					return false;
				mins.push_back((y-limit)/x);
			}
			sort(mins.begin(), mins.end());
			for(int i = 0; i < (int)upCows.size(); i++) {
				if(upCows[i] > mins[i])
					return false;
			}
			return true;
		};
		
		//binary search for the lowest upper limit of downward cows
		ll topSmall = -2e18, topBig = 2e18;
		while(topSmall <= topBig) {
			ll mid = (topSmall+topBig)/2;
			if(checkTop(mid))
				topBig = mid-1;
			else
				topSmall = mid+1;
		}		
		//another binary search for the highest lower limit of upward cows
		ll botSmall = -2e18, botBig = 2e18;
		while(botSmall <= botBig) {
			ll mid = (botSmall+botBig)/2;
			if(checkBot(mid))
				botSmall = mid+1;
			else
				botBig = mid-1;
		}

		//answer is then the difference between these two limits
		cout << topSmall-botBig << "\n";
	}
}