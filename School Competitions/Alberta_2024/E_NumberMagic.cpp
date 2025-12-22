#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef __int128 ll;

ll addOnes(ll val) {
	ll add = 0;
	ll pow = 1;
	while(pow <= val) {
		add += pow;
		pow *= 10;
	}
	return val+add;
}

pair<ll, ll> subtractOnes(ll val) {
	ll add = 0;
	ll pow = 1;
	while(pow*10 <= val) {
		add += pow;
		pow *= 10;
	}
	ll res1 = val-add;
	add += pow;
	ll res2 = val-add;
	
	pair<ll, ll> ans = {-1, -1};
	
	if(addOnes(res1) == val)
		ans.first = res1;
	if(addOnes(res2) == val)
		ans.second = res2;
	return ans;

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long N;
	int Q;
	cin >> N >> Q;
	ll n = N;
	set<ll> seen;
	queue<pair<ll, int>> q;
	q.push({n, 0});
	while(!q.empty()) {
		auto curr = q.front();
		q.pop();

		if(seen.count(curr.first))
			continue;
		seen.insert(curr.first);
		
		if(curr.second >= 24)
			continue;
		if(curr.first > 1)
			q.push({curr.first/2, curr.second+1});
		q.push({addOnes(curr.first), curr.second+1});
	}
	while(Q-->0) {
		long long val;
		cin >> val;
		q = queue<pair<ll, int>>();
		set<ll> mySeen;
		q.push({val, 0});
				
		bool found = false;
		while(!q.empty()) {
			auto curr = q.front();
			q.pop();

			if(seen.count(curr.first)) {
				found = true;
				break;
			}
			if(mySeen.count(curr.first))
				continue;
			mySeen.insert(curr.first);
			if(curr.second >= 8)
				continue;
			
			if(curr.first <= (ll)(1e18)) {
				q.push({curr.first*2, curr.second+1});
				q.push({curr.first*2+1, curr.second+1});
			}
			
			auto res = subtractOnes(curr.first);
			if(res.first != -1)
				q.push({res.first, curr.second+1});
			if(res.second != -1)
				q.push({res.second, curr.second+1});
			
		}
		
		if(found) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}